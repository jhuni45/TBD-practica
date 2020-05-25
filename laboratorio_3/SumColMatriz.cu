%%cu
#include <assert.h> 
#include <cuda_runtime.h> 
#include <device_functions.h>
#include <device_launch_parameters.h>
#include <stdio.h> 

__global__ void SumaColMatrizKernel_0(int M, int N, float* Md, float* Nd){
    // Pvalue es usado para el valor intermedio
    int Pvalue = 0;
    int columna = blockIdx.x * blockDim.x + threadIdx.x;
    int posIni = columna * M;
        for (int k = 0; k < M; ++k) {
            Pvalue = Pvalue + Md[posIni + k];
        }
    Nd[columna] = Pvalue;
}
