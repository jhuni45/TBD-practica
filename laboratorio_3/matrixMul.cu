#include <assert.h> 
#include <cuda_runtime.h> 
#include <helper_functions.h> 
#include <helper_cuda.h> 
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

__global__ void SumaColMatrizKernel_1(int M, float* Md, float* Nd)
{
    // Pvalue es usado para el valor intermedio
    int Pvalue = 0;
    int columna = threadIdx.x;
    int posIni = columna * M;
    for (int k = 0; k < M; ++k) {
        for (int k =
            0; k < M; ++k) {
            Pvalue = Pvalue + Md[posIni + k];
        }
        Nd[columna] = Pvalue;
    }
}

__global__ void SumaColMatrizKernel_2(int M, int N, float* Md, float* Nd)
{
    // Pvalue es usado para el valor intermedio
    int Pvalue = 0;
    int columna = blockIdx.x * blockDim.x + threadIdx.x;
    int posIni = columna * M;
        for (int k = 0; k < M; ++k) {
            Pvalue = Pvalue + Md[posIni + k];
        }
    Nd[columna] = Pvalue;
}

__global__ void SumaColMatrizKernel_3(int M, float* Md, float* Nd)
{
    // Pvalue es usado para el valor intermedio
    int Pvalue = 0;
    int columna = blockIdx.x;
    int pasos = M / blockDim.x;
    int posIni = columna * M + threadIdx.x * pasos;
    for (int k = 0; k < pasos; ++k) {
        Pvalue = Pvalue + Md[posIni + k];
    }
    atomicAdd(&(Nd[columna]), Pvalue);
}

__global__ void SumaColMatrizKernel_4(int M, int N, float* Md, float* Nd)
{
    // Pvalue es usado para el valor intermedio
    int Pvalue = 0;
    int columna = blockIdx.y * (N / gridDim.x) + threadIdx.x;
    int pasos = M / blockDim.x;
    int posIni = columna * M + threadIdx.x * pasos;
    for (int k = 0; k < pasos; ++k) {
        Pvalue = Pvalue + Md[posIni + k];
    }
    atomicAdd(&(Nd[columna]), Pvalue);
}

    // Lanzamiento del kernel 5 con memoria compartida  
#define DIMBLOCKX 32

__global__ void SumaColMatrizKernel_5(int M, float* Md, float* Nd)
{
    __shared__ float Nds[DIMBLOCKX];
    int Pvalue = 0;
    int columna = blockIdx.x;
    int pasos = M / blockDim.x;
    int posIni = columna * M + threadIdx.x * pasos;
    for (int k = 0; k < pasos; ++k) {
        Pvalue = Pvalue + Md[posIni + k];
    }
    atomicAdd(&(Nd[columna]), Pvalue);
    // Nds[threadIdx.x] = Pvalue;

    __syncthreads();
    if (threadIdx.x == 0)
    {
        for (int i = 1; i < blockDim.x; ++i) {
            Nds[0] = Nds[0] + Nds[i];
        }
        atomicAdd(&(Nd[blockIdx.y]), Nds[0]);
        // Nd[blockIdx.y] = Nds[0];
    }
}


void SumaColMatriz(int M, int N, float* Mh, float* Nh)
{
    int size = M * N * sizeof(int);
    int size2 = N * sizeof(float);
    float* Md, * Nd;

    // Asignar en dispositivo
    cudaMalloc(&Md, size);
    cudaMalloc(&Nd, size2);

    // Inicializo matrices en el dispositivo
    cudaMemcpy(Md, Mh, size, cudaMemcpyHostToDevice);
    cudaMemset(Nd, 0, size2);
    // Invocar el kernel que suma en GPU

    /*--------- KERNEL 0 ---------*/
    // SumaColMatrizKernel_0 << <N, 1 >> > (M, Md, Nd);

    /*--------- KERNEL 1 ---------*/
    // SumaColMatrizKernel_1 << <1, N >> > (M, Md, Nd);
    // dim3 tamGrid(1, 1); //Grid dimensión
    // dim3 tamBlock(N, 1, 1); //Block dimensión
    // SumaColMatrizKernel_1 << <1, N >> > (M, Md, Nd);

    /*--------- KERNEL 2 ---------*/
    // int bloques = N / 128; // se asume N múltiplo de 128
    // dim3 tamGrid(bloques, 1); //Grid dimensión
    // dim3 tamBlock(128, 1, 1); //Block dimensión
    // SumaColMatrizKernel_2 << <bloques, 128 >> > (M, Md, Nd);

    /*--------- KERNEL 3 ---------*/
    // int chunk = 32; // Se asume M múltiplo de 32
    // dim3 tamGrid(N / chunk, 1); //Grid dimensión
    // dim3 tamBlock(M / chunk, chunk, 1); //Block dimensión
    // SumaColMatrizKernel_3 << <N, M / chunk >> > (M, Md, Nd);

    /*--------- KERNEL 4 ---------*/
    /* Si quiero que un bloque procese más de una columna */
    // int chunk = 32; // Se asume M y N múltiplos de 32
    // dim3 tamGrid(N / chunk, 1); //Grid dimensión
    // dim3 tamBlock(M / chunk, chunk, 1); //Block dimensión
    // SumaColMatrizKernel_4 << <tamGrid, tamBlock >> > (M, N, Md, Nd);


    // Lanzamiento del kernel 5 con memoria compartida
    /*--------- KERNEL 5 ---------*/
    // configuración de la ejecución
    int chunk = 32;
    dim3 tamGrid(N, 1); //Grid dimensión
    dim3 tamBlock(M / chunk, 1, 1); //Block dimensión
    SumaColMatrizKernel_5 << <tamGrid, tamBlock >> > (M, Md, Nd); /* lanzamiento del kernel */

    /*--------- TRAER RESULTADO ---------*/
    // Traer resultado;
    cudaMemcpy(Nh, Nd, size2, cudaMemcpyDeviceToHost);
    // Free matrices en device
    cudaFree(Md);
    cudaFree(Nd);
}

int main(void){
    int M = 1024;
    int N = 512;
    float** matriz;
    matriz = new float* [M];
    // En la posicion cero, se colaca todo el vector
    matriz[0] = new float[M * N];

    for (int i = 1; i < M; i++) {
        matriz[i] = &matriz[0][N];
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = 1;
        }
    }

    float* Nh;
    Nh = new float[N];

    SumaColMatriz(M, N, matriz[0], Nh);
    for (int j = 0; j < N; j++){
        printf("%f ", Nh[j]);
    }

    return 0;
}