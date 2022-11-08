/* Crear un algoritmo que realice el producto escalar de dos vectores donde el tamaño de los vectores es de NP (cantidad de procesos lanzados) por 5.

   Para realizar el producto escalar, lo que vamos a tener que hacer, es enviar a cada proceso una porcion de los vectores originales con `MPI_Scatter`.
   Cada proceso ira haciendo el producto de los elementos de los vectores que recibió almacenadolos en una variable `producto`. Luego todos los productos locales se reducirán en el proceso 0 con `MPI_Reduce`.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 5

int main(int argc, char *argv[]) {
    int rank, size, i, producto, total = 0;
    int *vectorA, *vectorB, *vectorAlocal, *vectorBlocal;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        vectorA = (int *)malloc(N * sizeof(int));
        vectorB = (int *)malloc(N * sizeof(int));
        for (i = 0; i < N; i++) {
            vectorA[i] = i;
            vectorB[i] = i;
        }
    }

    vectorAlocal = (int *)malloc((N / size) * sizeof(int));
    vectorBlocal = (int *)malloc((N / size) * sizeof(int));

    MPI_Scatter(vectorA, N / size, MPI_INT, vectorAlocal, N / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vectorB, N / size, MPI_INT, vectorBlocal, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < N / size; i++) {
        producto += vectorAlocal[i] * vectorBlocal[i];
    }

    
    MPI_Reduce(&producto, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    

    if (rank == 0) {
        printf("Producto escalar: %d

", producto);
    }

    MPI_Finalize();
    return 0;
}