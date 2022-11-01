#include "mpi.h"
#include <iostream>
#include <time.h>

#define TAMANIO 5

int main(int argc, char *argv[]) 
{
    using namespace std;

    int rank, size, contador, maximo;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Creacion y relleno de los vectores
    int elementos_vector = TAMANIO * size; //cantidad de elementos de los vectores principales
    int Vector[elementos_vector]; //vector principal
    srand(time(NULL));
    for (int i = 0; i < TAMANIO; i++)
    {
        Vector[TAMANIO*rank+i] = rand()%(100); // Vector recibe valores aleatorios entre 0 y 99
    } 

    // Repartimos los valores del vector
    MPI_Bcast(
        &Vector,                // Valores a compartir en cada proceso
        elementos_vector,       // Cantidad de elementos a compartir en cada proceso
        MPI_INT,                // Tipo del dato que se compartirá
        0,                      // proceso principal que reparte los datos
        MPI_COMM_WORLD);        // Comunicador (En este caso, el global)

    contador = 0;
    for (int i = 0; i < elementos_vector; i++)
    {
        contador += (Vector[i] % Vector[rank] == 0) ? 1 : 0;
    }
    cout << "Cantidad contada en el proceso " << rank << ":" << contador << endl;

    /*
       Reunimos los datos en un solo proceso, aplicando una operacion
       lǵica, en este caso, el máximo.
    */
    MPI_Reduce(
        &contador,        //Elemento a enviar (cada proceso la enviará)
        &maximo,          //Variable donde se almacena la reunion de los datos
        1,                //Cantidad de datos a reunir
        MPI_INT,          //Tipo del dato que se reunira
        MPI_MAX,          //Operacion aritmetica a aplicar
        0,                //Proceso que recibira los datos
        MPI_COMM_WORLD);  //Comunicador a utilizar, el global

    if (rank == 0)
    {
    	cout << "Se imprime vector:" << endl;
        for(int i = 0; i < elementos_vector; i++)
        {
            cout << " " << Vector[i];
	}
        cout << endl;
        cout << "La cantidad maxima es: " << maximo << endl;
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

