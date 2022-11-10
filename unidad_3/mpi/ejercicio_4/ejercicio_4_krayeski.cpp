#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    //Variables 
    int rank, size, total, elementos;

    MPI_Init(&argc, &argv); 

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    elementos = 5;
    //5, según la consigna
    total = size * elementos;

    // vectores
    float vector1[total], vector2[total];
    float vector1_local[elementos], vector2_local[elementos];

    // Variables para la suma de los vectores
    float suma_parcial;                      // Suma parcial por vector
    float sumas_parciales[size], suma_total; // Suma parcial que ocupa el proceso Raiz.

    //Inicializacion
    suma_total = 0;
    suma_parcial = 0;

    if (rank == 0)
    {
        for (int i = 0; i < total; i++)
        {
            vector1[i] = i + 3;
            vector2[i] = i + 2;
        }
    }

    // Aplico MPI_Scatter 
    MPI_Scatter(vector1, elementos, MPI_FLOAT, vector1_local, elementos, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Aplico MPI_Scatter 
    MPI_Scatter(vector2, elementos, MPI_FLOAT, vector2_local, elementos, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Se realiza el calculo parcial sobre el vector principal
    for (int i = 0; i < elementos; i++)
    {
        suma_parcial = suma_parcial + (vector1_local[i] * vector2_local[i]);
        cout << "Proceso: " << rank
             << " vector1: " << vector1_local[i]
             << " vector2: " << vector2_local[i]
             << " resultado parcial: " << suma_parcial << endl;
    }

    // Se aplica MPI_Reduce sobre la sumatoria
    MPI_Reduce(&suma_parcial, &suma_total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Se realiza la suma en el proceso raiz
    if (rank == 0)
    {
        cout << "Suma Total: " << suma_total << endl;
    }

    MPI_Finalize();

    return 0;
}
