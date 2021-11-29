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
    struct
    {
        int quantity;
        int rank;
    } multiples, result;

    int vectorSize = size * SLICE;
    int vector[vectorSize];

    if (rank == ROOT)
    {
        for (int i = 0; i < vectorSize; i++)
        {
            vector[i] = rand() % 100;
        }

        cout << endl;
        cout << "VECTOR: " << endl;
        for (int i = 0; i < vectorSize; i++)
        {
            cout << vector[i] << " - ";
        }
        cout << endl;
    }

    MPI_Bcast(
        &vector,
        vectorSize,
        MPI_INT,
        ROOT,
        MPI_COMM_WORLD);

    int partialResults[vectorSize];
    multiples.rank = rank;
    multiples.quantity = 0;
    int isMultiple;
    for (int i = 0; i < vectorSize; i++)
    {
        isMultiple = vector[i] % vector[rank] == 0 ? true : false;
        if (isMultiple)
        {
            partialResults[multiples.quantity] = vector[i];
            multiples.quantity++;
        }
    }
    cout << endl;

    cout << endl;
    cout << "resultado parciales  de " << rank << endl;
    for (int i = 0; i < multiples.quantity; i++)
    {
        cout << partialResults[i] << " - ";
    }
    cout << endl;

    MPI_Reduce(
        &multiples,
        &result,
        1,
        MPI_2INT,
        MPI_MAXLOC,
        ROOT,
        MPI_COMM_WORLD);

    if (rank == ROOT)
    {
        cout << endl;
        cout << endl;
        cout << "EL QUE MAS MULTIPLOS TUVO FUE: " << endl;
        cout << "rango " << result.rank << " con " << result.quantity << " multiplos." << endl;
        cout << endl;
        cout << endl;
    }

    MPI_Finalize();

    return 0;
}