#include "utils.h"
#include <stdio.h>
#include <math.h>       /* ceil */

// Max Threads per block in GeForce 210
#define TxB 512


//Kernel operador not
__global__
void operator_and_kernel(const unsigned char* const inputImage, 
                         const unsigned char* const inputImage2,
                               unsigned char* const outputImage,
                               int numRows, int numCols)
{
  // El mapeo de los componentes uchar4 aRGBA es:
  // .x -> R ; .y -> G ; .z -> B ; .w -> A
  //Nota: Ignoramos el canal alfa
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if( i < numRows*numCols){
   
    if( (inputImage[i] == 255) && (inputImage2[i] == 255)  )
      outputImage[i] = 255;
    else
      outputImage[i] = 0;
    //Cambiamos si es 0:255 , si es 255:0
    //outputImage[i] = ( (inputImage[i] == 255) && (inputImage2[i] == 255) ) ? 255 : 0;
    //printf("%i and %i = %i  \n",inputImage[i], inputImage2[i], outputImage[i]);

  }
  
}

void operator_and_image(unsigned char* const d_inputImage, 
                        unsigned char* const d_inputImage2, 
                        unsigned char* const d_outputImage, 
                        size_t numRows, size_t numCols)
{

  // Dado que no importa la posicion relativa de los pixels
  // en este algoritmo, la estrategia para asignar hilos a
  // bloques y rejillas sera sencillamente la de cubrir
  // a todos los pixeles con hebras en el eje X
  long long int total_px = numRows * numCols;  // total pixels
  long int grids_n = ceil(total_px / TxB); // grids numer
  const dim3 blockSize(TxB, 1, 1);
  const dim3 gridSize(grids_n, 1, 1);
  operator_and_kernel<<<gridSize, blockSize>>>(d_inputImage, d_inputImage2, d_outputImage, numRows, numCols);
  
  cudaDeviceSynchronize(); 
  checkCudaErrors(cudaGetLastError());
}