#include "utils.h"
#include <stdio.h>
#include <math.h>       /* ceil */

// Max Threads per block in GeForce 210
#define TxB 512


//Kernel binarización de imagen
__global__
void image_binarization_kernel(const uchar4* const rgbaImage,
                               unsigned char* const outputImage,
                               int numRows, int numCols, int threshold)
{
  // El mapeo de los componentes uchar4 aRGBA es:
  // .x -> R ; .y -> G ; .z -> B ; .w -> A
  //Nota: Ignoramos el canal alfa
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if( i < numRows*numCols){
    uchar4 px = rgbaImage[i]; // thread pixel to process
    //printf( "Antes: R: %i G: %i B %i \n",px.x,px.y,px.z );
   
    //Primero se convierte a escala de grises

    unsigned char grey = .299f * px.x +
                         .587f * px.y +
                         .114f * px.z;

    //Binarizamos (si gris > threshold ? 255 : 0)

    outputImage[i] = ( grey > threshold) ? 255 : 0;

  }
  
}

void image_binarization(uchar4* const d_rgbaImage, 
                        unsigned char* const d_outputImage, 
                        size_t numRows, size_t numCols, int threshold)
{

  // Dado que no importa la posicion relativa de los pixels
  // en este algoritmo, la estrategia para asignar hilos a
  // bloques y rejillas sera sencillamente la de cubrir
  // a todos los pixeles con hebras en el eje X
  long long int total_px = numRows * numCols;  // total pixels
  long int grids_n = ceil(total_px / TxB); // grids numer
  const dim3 blockSize(TxB, 1, 1);
  const dim3 gridSize(grids_n, 1, 1);
  image_binarization_kernel<<<gridSize, blockSize>>>(d_rgbaImage, d_outputImage, numRows, numCols, threshold);
  
  cudaDeviceSynchronize(); 
  checkCudaErrors(cudaGetLastError());
}