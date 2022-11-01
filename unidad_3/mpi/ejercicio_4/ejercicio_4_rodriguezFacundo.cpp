#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 5

int main(int argc, char *argv[]) {
    int rank, size, i, producto, sumarizacionTotal = 0;
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

    MPI_Reduce(&producto, &sumarizacionTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Producto escalar: %d \n", producto);
    }

    MPI_Finalize();
    return 0;
}
