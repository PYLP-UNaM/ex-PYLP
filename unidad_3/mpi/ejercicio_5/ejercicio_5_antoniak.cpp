#include "mpi.h"
#include <iostream>
#include <time.h>

#define TAMANIO 5

int main(int argc, char *argv[]) 
{
    using namespace std;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Creacion y relleno de los vectores
    int elementos_vector = TAMANIO * size; //cantidad de elementos de los vectores principales
    int Vector[elementos_vector]; //vector principal
    int VectorLocal[TAMANIO];     //vector local para cada proceso
    srand(time(NULL));
    for (int i = 0; i < TAMANIO; i++)
    {
        Vector[TAMANIO*rank+i] = rand()%(100); // Vector A recibe valores aleatorios entre 0 y 99
    } 

    // Repartimos los valores del vector A
    MPI_Scatter(
        &Vector,                // Valores a dividir y compartir con cada proceso
        TAMANIO,                // Cantidad que se envia a cada proceso
        MPI_INT,                // Tipo del dato que se enviara
        &VectorLocal,           // Variable donde recibir los datos
        TAMANIO,                // Cantidad que recibe cada proceso
        MPI_INT,                // Tipo del dato que se recibira
        0,                      // proceso principal que reparte los datos
        MPI_COMM_WORLD);        // Comunicador (En este caso, el global)

    cout << "Datos del vector en el proceso " << rank << ":" << endl;
    for(int i = 0; i < TAMANIO; i++)
    {
	cout << " " << VectorLocal[i];
    }
    cout << endl;

    for (int i = 0; i < TAMANIO; i++)
    {
        VectorLocal[i] = (VectorLocal[i] % (rank+2) == 0) ? 1 : 0;
    }

    //Reunimos los datos en un solo proceso, aplicando una unión.
    MPI_Gather(
        &VectorLocal,           // Valores a juntar y recibir de cada proceso
        TAMANIO,                // Cantidad que se recibe a cada proceso
        MPI_INT,                // Tipo del dato que se recibirá
        &Vector,                // Variable donde juntar los datos
        TAMANIO,                // Cantidad que se junta por cada proceso
        MPI_INT,                // Tipo del dato que tendrá en la unión
        0,                      // Proceso principal que junta los datos
        MPI_COMM_WORLD);        // Comunicador (En este caso, el global)

    if (rank == 0)
    {
    	cout << "Se imprime vector tras operacion:" << endl;
        for(int i = 0; i < elementos_vector; i++)
        {
            cout << " " << Vector[i];
	}
        cout << endl;
    } 

    /*
       Terminamos la ejecucion de los procesos, despues de esto solo existira
       la hebra 0
       ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
       de codigo despues de "Finalize", es conveniente asegurarnos con una
       condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    */
    MPI_Finalize();
    return 0;
}

