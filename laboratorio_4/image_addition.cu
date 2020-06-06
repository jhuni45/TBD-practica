#include "utils.h"
#include <stdio.h>
#include <math.h>       /* ceil */

// Max Threads per block in GeForce 210
#define TxB 512


//Kernel suma media ponderada
__global__
void image_addition_kernel(const uchar4* const rgbaImage,
                           const uchar4* const rgbaImage2,
                                 uchar4* const outputImage,
                           int numRows, int numCols, float percent)
{
  // El mapeo de los componentes uchar4 aRGBA es:
  // .x -> R ; .y -> G ; .z -> B ; .w -> A
  //Nota: Ignoramos el canal alfa
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if( i < numRows*numCols){
    uchar4 px = rgbaImage[i]; // thread pixel to process
    uchar4 px2 = rgbaImage2[i]; // thread pixel to process
    //printf( "Antes: R: %i G: %i B %i \n",px.x,px.y,px.z );

    outputImage[i].x = ( percent * px.x ) + ( ( 1 - percent ) * px2.x );
    outputImage[i].y = ( percent * px.y ) + ( ( 1 - percent ) * px2.y );
    outputImage[i].z = ( percent * px.z ) + ( ( 1 - percent ) * px2.z );
    

    //printf( "Despues: R: %i G: %i B %i \n",outputImage[i].x,outputImage[i].y,outputImage[i].z );
  }
  
}

void image_addition(uchar4* const d_rgbaImage, 
                    uchar4* const d_rgbaImage2,
                    uchar4* const d_outputImage, 
                    size_t numRows, size_t numCols, float percent)
{

  // Dado que no importa la posicion relativa de los pixels
  // en este algoritmo, la estrategia para asignar hilos a
  // bloques y rejillas sera sencillamente la de cubrir
  // a todos los pixeles con hebras en el eje X
  long long int total_px = numRows * numCols;  // total pixels
  long int grids_n = ceil(total_px / TxB); // grids numer
  const dim3 blockSize(TxB, 1, 1);
  const dim3 gridSize(grids_n, 1, 1);
  image_addition_kernel<<<gridSize, blockSize>>>(d_rgbaImage, d_rgbaImage2, d_outputImage, numRows, numCols, percent);
  
  cudaDeviceSynchronize(); 
  checkCudaErrors(cudaGetLastError());
}