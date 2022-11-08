#include "mpi.h"
#include <iostream>
using namespace std;

#define ROOT 0
#define SLICE 5

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    struct { 
        int cantidad;
        int rank;
    } multiplos, result;

    int vectorSize = size * SLICE;
    int vector[vectorSize];

    if (rank == ROOT) {
        for (int i = 0; i < vectorSize; i++) {
            vector[i] = rand() % 100;
        }

        cout << endl;
        cout << "Vector: " << endl;
        for (int i = 0; i < vectorSize; i++) {
            cout << vector[i] << " - ";
        }
        cout << endl;

    }

    // Enviar a todos los procesos el vector
    MPI_Bcast(&vector, vectorSize, MPI_INT, ROOT, MPI_COMM_WORLD);

    int partialResults[vectorSize];
    multiplos.rank = rank;
    multiplos.cantidad = 0;
    int isMultiple;
    for (int i = 0; i < vectorSize; i++) {
        isMultiple = vector[i] % vector[rank] == 0 ? true : false;
        if (isMultiple){
            partialResults[multiplos.cantidad] = vector[i];
            multiplos.cantidad++;
        }
    }
    cout << endl;

    cout << endl;
    cout << "resultado parciales de " << rank << endl;
    for (int i = 0; i < multiplos.cantidad; i++) {
        cout << partialResults[i] << " - ";
    }
    cout << endl;

    MPI_Reduce(&multiplos, &result, 1, MPI_2INT, MPI_MAXLOC, ROOT, MPI_COMM_WORLD);

    if (rank == ROOT) {
        cout << endl;
        cout << endl;
        cout << "El proceso que mayor multiplos tuvo mediante la instruccion fue: " <<endl;
        cout << "rango " << result.rank << " con " << result.cantidad << " multiplos." <<endl;
        cout << endl;
        cout << endl;
    }

    MPI_Finalize();

    return 0;
}
