#include "utils.h"
#include <stdio.h>
#include <math.h>       /* ceil */
#include <map>
#include <vector>

// Max Threads per block in GeForce 210
#define TxB 512

__global__
void image_equalization_kernel(const uchar4* const rgbaImage,
                                     uchar4* const outputImage,
                                     int numRows, int numCols)
{
  // El mapeo de los componentes uchar4 aRGBA es:
  // .x -> R ; .y -> G ; .z -> B ; .w -> A
  //Nota: Ignoramos el canal alfa
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if( i < numRows*numCols){
    uchar4 px = rgbaImage[i]; // thread pixel to process
    //printf( "Antes: R: %i G: %i B %i \n",px.x,px.y,px.z );


    __shared__ unsigned int channelR[256];
    __shared__ unsigned int channelG[256];
    __shared__ unsigned int channelB[256];

    __shared__ unsigned int channelRacc[256];
    __shared__ unsigned int channelGacc[256];
    __shared__ unsigned int channelBacc[256];

    __shared__ unsigned char channelReq[256];
    __shared__ unsigned char channelGeq[256];
    __shared__ unsigned char channelBeq[256];


    if( i == 0 ){
      for(int q = 0; q < 256; q++ ){
        channelR[q]    = 0;
        channelG[q]    = 0;
        channelB[q]    = 0;
        channelRacc[q] = 0;
        channelGacc[q] = 0;
        channelBacc[q] = 0;
      }
    }

    __syncthreads();

    //Calcular histograma
    atomicAdd( &channelR[ px.x ] , 1);
    atomicAdd( &channelG[ px.y ] , 1);
    atomicAdd( &channelB[ px.z ] , 1);

    __syncthreads();

    if (i == 0){

      //Impresión del histograma
      // printf("Canal R \n");
      // for(int k = 0; k < 256; k++)
      //   printf("%i - %i \n", k, channelR[k]);
      
      // printf("Canal G \n");
      // for(int k = 0; k < 256; k++)
      //   printf("%i - %i \n", k, channelG[k]);

      // printf("Canal B \n");
      // for(int k = 0; k < 256; k++)
      //   printf("%i - %i \n", k, channelB[k]);        

      //Sumas acumuladas
      channelRacc[0] = channelR[0];
      channelGacc[0] = channelG[0];
      channelBacc[0] = channelB[0];
      for( int j = 1; j < 256; j++ ){
        channelRacc[j] = channelRacc[j-1] + channelR[j];
        channelGacc[j] = channelGacc[j-1] + channelG[j];
        channelBacc[j] = channelBacc[j-1] + channelB[j];
      }

      // printf("Canal R acc \n");
      // for(int k = 0; k < 256; k++)
      //   printf("%i - %i \n", k, channelRacc[k]);

    }

    __syncthreads();
    //Ecualizamos con los primeros 256 hilos.
    if(i < 256){

      channelReq[i] = round((float)channelRacc[i] * 255.0/( (float)numRows*numCols ) );
      channelGeq[i] = round((float)channelGacc[i] * 255.0/( (float)numRows*numCols ) );
      channelBeq[i] = round((float)channelBacc[i] * 255.0/( (float)numRows*numCols ) );

    }
    
    __syncthreads();

    outputImage[i].x =  channelReq[px.x];
    outputImage[i].y =  channelGeq[px.y];
    outputImage[i].z =  channelBeq[px.z];

    __syncthreads();
    //printf( "Despues: R: %i G: %i B %i \n",outputImage[i].x,outputImage[i].y,outputImage[i].z );
  }
  
}

void image_equalization(uchar4 * const d_rgbaImage,
                  uchar4* const d_outputImage, size_t numRows, size_t numCols)
{

  // Dado que no importa la posicion relativa de los pixels
  // en este algoritmo, la estrategia para asignar hilos a
  // bloques y rejillas sera sencillamente la de cubrir
  // a todos los pixeles con hebras en el eje X
  long long int total_px = numRows * numCols;  // total pixels
  long int grids_n = ceil(total_px / TxB); // grids numer
  const dim3 blockSize(TxB, 1, 1);
  const dim3 gridSize(grids_n, 1, 1);
  image_equalization_kernel<<<gridSize, blockSize>>>(d_rgbaImage, d_outputImage, numRows, numCols);
  
  cudaDeviceSynchronize(); 
  checkCudaErrors(cudaGetLastError());
}