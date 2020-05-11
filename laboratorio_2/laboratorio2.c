#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 10
#define N 10

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

    printf("no. de filas = ");
    scanf("%d", &rows);
    printf("no. of columnas = ");
    scanf("%d", &columns);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("a[%d][%d] = \n", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    printf("\nLa matriz es: \n");
    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++)
            printf("%d ", a[i][j]);
    printf("\n");
    }

    
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

    for (i=0; i < rows; i++) {
        printf("Los valores resultantes son %d\n",s[i]);
    }

    return 0;
    }