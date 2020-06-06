#include "utils.h"
#include <stdio.h>
#include <math.h>       /* ceil */

// Max Threads per block in GeForce 210
#define TxB 512

__global__
void gamma_correction_kernel(const uchar4* const rgbaImage,
                       uchar4* const outputImage,
                       int numRows, int numCols, float gamma)
{
  // El mapeo de los componentes uchar4 aRGBA es:
  // .x -> R ; .y -> G ; .z -> B ; .w -> A
  //Nota: Ignoramos el canal alfa
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if( i < numRows*numCols){
    uchar4 px = rgbaImage[i]; // thread pixel to process
    //printf( "Antes: R: %i G: %i B %i \n",px.x,px.y,px.z );

    unsigned char rcolor = round(pow((px.x / 255.0f), (1.0f / gamma)  ) * 255.0f);
    outputImage[i].x = (rcolor > 255.0f) ? 255.0f : rcolor;
    outputImage[i].x = (rcolor < 0) ? 0 : rcolor;
    unsigned char gcolor = round(pow((px.y / 255.0f), (1.0f / gamma)  ) * 255.0f);
    outputImage[i].y = (gcolor > 255.0f) ? 255.0f : gcolor;
    outputImage[i].y = (gcolor < 0) ? 0 : gcolor;
    unsigned char bcolor = round(pow((px.z / 255.0f), (1.0f / gamma)  ) * 255.0f);
    outputImage[i].z = (bcolor > 255.0f) ? 255.0f : bcolor;
    outputImage[i].z = (bcolor < 0) ? 0 : bcolor;


    //printf( "Despues: R: %i G: %i B %i \n",outputImage[i].x,outputImage[i].y,outputImage[i].z );
  }
  
}

void gamma_correction(uchar4 * const d_rgbaImage,
                  uchar4* const d_outputImage, size_t numRows, size_t numCols, float gamma)
{

  // Dado que no importa la posicion relativa de los pixels
  // en este algoritmo, la estrategia para asignar hilos a
  // bloques y rejillas sera sencillamente la de cubrir
  // a todos los pixeles con hebras en el eje X
  long long int total_px = numRows * numCols;  // total pixels
  long int grids_n = ceil(total_px / TxB); // grids numer
  const dim3 blockSize(TxB, 1, 1);
  const dim3 gridSize(grids_n, 1, 1);
  gamma_correction_kernel<<<gridSize, blockSize>>>(d_rgbaImage, d_outputImage, numRows, numCols, gamma);
  
  cudaDeviceSynchronize(); 
  checkCudaErrors(cudaGetLastError());
}