# SUMA DE COLUMNAS DE UNA MATRIZ
## Integrantes
- Basurco Cayllahua, Eduardo Rolando
- Chavez Cruz, Jhunior Kenyi
- Humpire Cutipa, Hayde Luzmila
- Larraondo Lamchog, Alejandro Jesús 

## Preliminares
- Realizar la suma de columnas de una matriz.
  - Resultado de la suma columnas de una matriz.
  
## Requerimientos
### Inicializar el entorno CUDA en Google Colab
```cuda
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
## Kernel con Memoria Compartida
- Es cientos de veces más rápida que la memoria global.
- Puede usarse como una especie de caché para reducir los accesos a memoria global.
- Permite que los hilos de un mismo bloque puedan cooperar.
- Se puede usar para evitar accesos no coalesced a la memoria global:
  – Los datos se guardan en forma intermedia en la memoria compartida.
  – Se reordena el acceso a los datos para que cuando se copien de memoria compartida a memoria global el acceso sea coalesced.

### Hagamos un kernel (kernel 5) que utilice memoria compartida para sumar matrices 
```cuda
__shared __float Nds[DIMBLOCKX];
__syncthreads(); 
```

### Lanzamiento del kernel memoria compartida
```cuda
/ Lanzamiento del kernel 5 con memoria compartida
    /*--------- KERNEL 5 ---------*/
    /* configuración de la ejecución */
    int chunk = 32;
    dim3 tamGrid(N, 1); //Grid dimensión
    dim3 tamBlock(M / chunk, 1, 1); //Block dimensión
    SumaColMatrizKernel_5 <<<tamGrid, tamBlock >>> (M, Md, Nd); /* lanzamiento del kernel */
```
### Kernel 5 memoria compartida
```cuda
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
```

## Compilación y ejecución de código

```terminal
$ gcc laboratorio2.c -lpthread -o laboratorio2
$ ./laboratorio2
```
### Resultado para matriz de 1024x512
