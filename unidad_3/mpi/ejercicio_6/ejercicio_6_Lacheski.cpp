#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, num, cantMultiplos, maxGlobal;

    MPI_Init(&argc, &argv);  

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    num = 5;
    maxGlobal = 0;
    cantMultiplos = 0;
    lng = size * num;
    int vectorPrincipal[lng];

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

    MPI_Bcast(
        &vectorPrincipal[0], lng, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < lng; i++){
        if (vectorPrincipal[i] % vectorPrincipal[rank] == 0){
            cantMultiplos ++;
        }
    }

    printf("Soy proceso %d; encontre %d multiplos del elemento %d\n", rank, cantMultiplos, vectorPrincipal[rank]);

    MPI_Reduce(&cantMultiplos, &maxGlobal, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        printf("La mayor cantidad de multiplos obtenidos por un proceso es: %d \n", maxGlobal);
    }

    MPI_Finalize(); 

    return 0;
}