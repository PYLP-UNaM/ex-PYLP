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

    int vectorSize = size * SLICE;
    int vector[vectorSize], result[vectorSize];
    int mailbox[SLICE];

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

    MPI_Scatter(
        &vector,
        SLICE,
        MPI_INT,
        &mailbox,
        SLICE,
        MPI_INT,
        ROOT,
        MPI_COMM_WORLD);

    cout << endl;
    cout << "MAIL BOX  de " << rank << endl;
    for (int i = 0; i < SLICE; i++)
    {
        cout << mailbox[i] << " - ";
    }
    cout << endl;

    int partialResults[SLICE];
    for (int i = 0; i < SLICE; i++)
    {
        partialResults[i] = mailbox[i] % (rank + 2) == 0 ? 1 : 0;
    }
    cout << endl;

    MPI_Gather(
        &partialResults,
        SLICE,
        MPI_INT,
        &result,
        SLICE,
        MPI_INT,
        ROOT,
        MPI_COMM_WORLD);

    if (rank == ROOT)
    {
        cout << endl;
        cout << endl;
        cout << endl;
        // IMPRIMIR VECTOR
        cout << "RESULTADO: " << endl;
        for (int i = 0; i < vectorSize; i++)
        {
            cout << result[i] << " - ";
        }
        cout << endl;
        cout << endl;
    }

    MPI_Finalize();

    return 0;
}