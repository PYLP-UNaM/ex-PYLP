/* Crear un algoritmo donde el proceso 0 cree y envíe un vector *"Global"* de tamaño NP(cantidad de procesos lanzados) \* 5 a todos procesos mediante `MPI_Bcast`. 

Cada proceso va a recibir dicho valores, utilizando la misma variable de origen.

Cada proceso debe ir contabilizando todos los elementos del vector, que sean multiplo del elemento en la posicion `rango` del proceso.

> el proceso 0 debe verificar cuantos elementos son multiplos del elemento en la posicion 0

> el proceso 1 debe verificar cuantos elementos son multiplos del elemento en la posicion 1

> el proceso 2 debe verificar cuantos elementos son multiplos del elemento en la posicion 2

> el proceso n debe verificar cuantos elementos son multiplos del elemento en la posicion n

Luego imprimir el resultado por pantalla y opcionalmente obtener cual es el que mayor multiplos tuvo mediante la instruccion `MPI_Reduce` .*/

#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *vector = new int[size * 5];
    int *vector_local = new int[5];

    if (rank == 0)
    {
        srand(time(NULL));
        for (int i = 0; i < size * 5; i++)
        {
            vector[i] = rand() % 10;
        }
    }

    MPI_Bcast(vector, size * 5, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 5; i++)
    {
        vector_local[i] = vector[rank * 5 + i];
    }

    int contador = 0;
    for (int i = 0; i < size * 5; i++)
    {
        if (vector[i] % vector_local[rank] == 0)
        {
            contador++;
        }
    }

    cout << "Proceso " << rank << " tiene " << contador << " multiplos de " << vector_local[rank] << endl;

    MPI_Finalize();
    return 0;
}