#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, num;

    MPI_Init(&argc, &argv);  

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    num = 5;
    lng = size * num;
    int vectorPrincipal[lng];
    int vectorLocal[num];

    if (rank == 0){

        for (int i = 0; i < lng; i++){
            vectorPrincipal[i] = rand() % 100;
        }

        printf("Vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipal[i]);
        }

        printf("\n\n");
    }

    MPI_Scatter(&vectorPrincipal[0], num,MPI_INT, &vectorLocal[0], num, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < num; i++){
        if (vectorLocal[i] % (rank + 2) == 0){
            vectorLocal[i] = 1;
        } else {
            vectorLocal[i] = 0;
        }
    }

    MPI_Gather(&vectorLocal[0], 5, MPI_INT, &vectorPrincipal[0], 5, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) { 
        printf("El resultado es el siguiente vector: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -",vectorPrincipal[i]); 
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
} 