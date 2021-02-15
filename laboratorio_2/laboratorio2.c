#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define M 1024
#define N 512

int rows, columns, a[M][N], s[M];

void* f(void* p) {
   int k = *((int*) p);
   int i;
   for (i = 0; i < columns; i++) {
      s[k] += a[i][k];
   }
   return NULL;
}

int main() {
	srand(time(NULL));
    int i, j, *p, rc;
    int sum = 0;
    pthread_t th[M];
    clock_t parallelT, secuentialTstart, secuentialTend;
    int secuential[M];

    rows = M;
    columns = N;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            a[i][j] = 1;
        }
    }
/*row
    printf("\nLa matriz es: \n");
    for(i=0; i < rows; i++) {1
        for(j=0; j < columns; j++)
            printf("%d ", a[i][j]);
    printf("\n");
    }*/
    //threads
    parallelT=clock();
    for (i=0; i < rows; i++) {
        p = malloc(sizeof(int));
        *p = i;
        rc = pthread_create(&th[i], NULL, f, p);
        if (rc != 0) {
            printf("Error");
            exit(-1);
        }
    }
    
    for (i=0; i < rows; i++) {
        pthread_join(th[i], NULL);
    }
    parallelT=clock()-parallelT;
    
    secuentialTstart=clock();
    //secuencial
    int acum=0;
    for (i = 0; i < N; i++){
        for ( j = 0; j < M; j++){
           acum+=a[j][i];
        }  
        printf("acumulado: %d \n",acum);  
    }
    secuentialTend=clock();
    printf("Para matriz %dx%d\n",M,N);
    printf("El tiempo para la compilacion secuencial es :\n");
    printf("=> %f\n",(double)(secuentialTend-secuentialTstart)/CLOCKS_PER_SEC);
    printf("El tiempo para la compilacion con threads es :\n");
    printf("=> %f\n",(double)parallelT/CLOCKS_PER_SEC);
    printf("Suma de toda la matriz: %d\n",acum);

    return 0;
    }