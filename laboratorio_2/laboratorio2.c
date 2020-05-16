#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>


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
    int i, j, *p, rc;
    int sum = 0;
    pthread_t th[M];
    clock_t firstT, secondT;
    int secuential[M];

    rows = 1024;
    columns = 512;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            a[i][j] = rand() % 5;
        }
    }

    /*printf("\nLa matriz es: \n");
    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++)
            printf("%d ", a[i][j]);
    printf("\n");
    }*/
    //threads
    firstT=clock();
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
    firstT=clock()-firstT;
    
    secondT=clock();
    //secuencial
    for (i = 0; i < N; i++)
    {
        for ( j = 0; j < M; j++)
        {
            secuential[j] = secuential[i]+a[j][i];
        }
        
    }
    secondT=clock()-secondT;
    
    printf("El tiempo para la compilacion secuencial es :\n");
    printf("- %ld\n",secondT);
    printf("El tiempo para la compilacion con threads es :\n");
    printf("- %ld\n",firstT);
    /*for (i=0; i < rows; i++) {
        printf("Los valores resultantes son %d\n",s[i]);
    }*/

    return 0;
    }