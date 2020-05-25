# SUMA DE COLUMNAS DE UNA MATRIZ
## Integrantes
- Basurco Cayllahua, Eduardo Rolando
- Chavez Cruz, Jhunior Kenyi
- Humpire Cutipa, Hayde Luzmila
- Larraondo Lamchog, Alejandro Jesús 

## Preliminares
- Realizar la suma de columnas de una matriz que utilice memoria compartida..
  - Resultado de la suma columnas de una matriz utilizando memoria compartida.
  
## Requerimientos

### Kernel con Memoria Compartida
- Es cientos de veces más rápida que la memoria global.
- Puede usarse como una especie de caché para reducir los accesos a memoria global.
- Permite que los hilos de un mismo bloque puedan cooperar.
- Dimensión pequeña.
- Se puede usar para evitar accesos no coalesced a la memoria global:
  - Los datos se guardan en forma intermedia en la memoria compartida.
  - Se reordena el acceso a los datos para que cuando se copien de memoria compartida a memoria global el acceso sea coalesced.

### Inicializar el entorno CUDA en Google Colab
Ejecutar un programa Cuda para tarjetas Nvidia via Online con ayuda de una maquina virtual. Si no tienes una pc  con una tarjeta de video Nvidia para realizar programacion paralela, google colab nos brinda una maquina virtual en su plataforma Google Colab.
```codigo
!apt-get --purge remove cuda nvidia* libnvidia-*
!dpkg -l | grep cuda- | awk '{print $2}' | xargs -n1 dpkg --purge
!apt-get remove cuda-*
!apt autoremove
!apt-get update

!wget https://developer.nvidia.com/compute/cuda/9.2/Prod/local_installers/cuda-repo-ubuntu1604-9-2-local_9.2.88-1_amd64 -O cuda-repo-ubuntu1604-9-2-local_9.2.88-1_amd64.deb
!dpkg -i cuda-repo-ubuntu1604-9-2-local_9.2.88-1_amd64.deb
!apt-key add /var/cuda-repo-9-2-local/7fa2af80.pub
!apt-get update
!apt-get install cuda-9.2
!pip install git+git://github.com/andreinechaev/nvcc4jupyter.git
%load_ext nvcc_plugin
```

## Hagamos un kernel (kernel 6) que utilice memoria compartida  y memoria bidimensional para sumar matrices 
```cuda
__shared __float Nds[DIMBLOCKX];
__syncthreads(); 
```

### Lanzamiento del kernel 6 memoria compartida y memoria bidimensional
```cuda
// Lanzamiento del kernel 6 con memoria compartida y memoria bidimensional
    /*--------- KERNEL 6 ---------*/
    /* configuración de la ejecución */
    int chunk = 32; // Se asume M y N múltiplos de 32
    dim3 tamGrid(N / chunk, 1); //Grid dimensión
    dim3 tamBlock(M / chunk, chunk, 1); //Block dimensión
    SumaColMatrizKernel_6 <<<tamGrid, tamBlock >>> (M, N, Md, Nd); /* lanzamiento del kernel */
```
### Kernel 6 memoria compartida  y memoria bidimensional
```cuda
// Lanzamiento del kernel 6 con memoria compartida y memoria bidimensional
#define DIMBLOCKX 32
__global__ void SumaColMatrizKernel_6(int M, int N, float* Md, float* Nd)
{
    __shared__ float Nds[DIMBLOCKX];
    // Pvalue es usado para el valor intermedio
    int Pvalue = 0;
    int columna = blockIdx.y * (N / gridDim.x) + threadIdx.x;
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
```

## Compilación y ejecución de código
### En ubuntu:

```terminal
$ nvcc SumColMatriz.cu 
$ ./a.out
```
### Resultado para matriz de 1024x512


## Reduce
- Reducción en paralelo de la suma.
- Los datos se copian inicialmente de la memoria global a la memoria compartida.
- Solamente se realiza la primera etapa de la reducción. 

### Para declarar la memoria compartida se puede usar una constante:
```cuda
#define CANT_HILOS 128
__global__ void reduction(float * output, float * input) {
 __shared__ float intermedio[CANT_HILOS];
 …
};
reduction <<<N_BLOCK,CANT_HILOS>>> (output,input);
```

### Para declarar la memoria compartida se puede hacer en forma dinámica con extern:
```cuda
__global__ void reduction(float * output, float * input) {
 extern __shared__ float intermedio[];
 …
};
reduction <<<N_BLOCK,CANT_HILOS,
 CANT_HILOS*sizeof(float)>>> (output,input);
```
