
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
using namespace std;

__global__ void MatrixSumKernel(int M, float* Md, float* Nd) {
    // Pvalue es usado para el valor intermedio
    float Pvalue = 0;
    int aux = threadIdx.y * M;
    for (int k = 0; k < M; ++k) {
        Pvalue = Pvalue + Md[aux + k];
    }
    Nd[threadIdx.y] = Pvalue;
}

void SumaColMatrizDevice(float M, float N, float* Mh, float* Nh) {
    int size = M * N * sizeof(float), size2 = N * sizeof(float);
    float* Md, * Nd;
    // Allocate en device
    cudaMalloc(&Md, size);
    cudaMalloc(&Nd, size2);
    // Inicializo matrices en el device
    cudaMemcpy(Md, Mh, size, cudaMemcpyHostToDevice);
    cudaMemset(Nd, 0, N * sizeof(float));
    // Invocar el kernel que suma en GPU
    dim3 tamGrid(1, 1); //Grid dimensión
    dim3 tamBlock(1, N, 1); //Block dimensión
    // lanzamiento del kernel
    MatrixSumKernel << <tamGrid, tamBlock >> > (M, Md, Nd);
    // Traer resultado;
    cudaMemcpy(Nh, Nd, size, cudaMemcpyDeviceToHost);
    /*for (int k = 0; k < N; k++)
    {
        cout << "Valor del Vector:" << Nh[k] << endl;
    }*/
    // Free matrices en device
    cudaFree(Md); cudaFree(Nd);
}

int main()
{
    //fila, columna
    int i, j,a;
    float m = 3;
    float n = 3;
    float* matriz;
    float* vector;
    vector = new float[n];
    matriz = new float[m * n];
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            a = i * n + j;
            matriz[a] = a;
            cout<<"Numero Añadido a la matriz" << matriz[a] << endl;
        }
    }
    for (int l = 0; l < n; l++)
    {
        vector[l] = 0;
        cout << "Vector de Suma" << vector[l] << endl;
    }

    SumaColMatrizDevice(m, n, matriz, vector);
    for (int k = 0; k < n; k++)
    {
        cout <<"Valor del Vector:" << vector[k] << endl;
    }
    return 0;
}