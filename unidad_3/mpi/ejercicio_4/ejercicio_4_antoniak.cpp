#include "mpi.h"
#include <iostream>
#include <time.h>

#define TAMANIO 5
 
int main(int argc, char *argv[]) 
{
    using namespace std;
    
    int rank, size, producto, total;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    // Creacion y relleno de los vectores
    int elementos_vector = TAMANIO * size; //cantidad de elementos de los vectores principales
    int VectorA[elementos_vector]; //vector principal A
    int VectorB[elementos_vector]; //vector principal B
    int VectorALocal[TAMANIO];     //vector local A para cada proceso
    int VectorBLocal[TAMANIO];     //vector local B para cada proceso
    srand(time(NULL));
    for (int i = 0; i < TAMANIO; i++)
    {
        VectorA[TAMANIO*rank+i] = rand()%(50); // Vector A recibe valores aleatorios entre 0 y 49
        VectorB[TAMANIO*rank+i] = 50+(rand()%(100)); // Vector B recibe valores aleatorios entre 50 y 149
    }

    // Repartimos los valores del vector A
    MPI_Scatter(
        &VectorA,                // Valores a dividir y compartir con cada proceso
        TAMANIO,				 // Cantidad que se envia a cada proceso
        MPI_INT,                 // Tipo del dato que se enviara
        &VectorALocal,           // Variable donde recibir los datos
        TAMANIO,				 // Cantidad que recibe cada proceso
        MPI_INT,                 // Tipo del dato que se recibira
        0,                       // proceso principal que reparte los datos
        MPI_COMM_WORLD);         // Comunicador (En este caso, el global)

    // Repartimos los valores del vector B
    MPI_Scatter(
        &VectorB,                // Valores a dividir y compartir con cada proceso
        TAMANIO,				 // Cantidad que se envia a cada proceso
        MPI_INT,                 // Tipo del dato que se enviara
        &VectorBLocal,           // Variable donde recibir los datos
        TAMANIO,				 // Cantidad que recibe cada proceso
        MPI_INT,                 // Tipo del dato que se recibira
        0,                       // proceso principal que reparte los datos
        MPI_COMM_WORLD);         // Comunicador (En este caso, el global)
 
    cout << "Datos del vector A en el proceso " << rank << ":" << endl;
    for(int i = 0; i < TAMANIO; i++)
    {
	    cout << " " << VectorALocal[i];
	}
    cout << endl;
    cout << "Datos del vector B en el proceso " << rank << ":" << endl;
    for(int i = 0; i < TAMANIO; i++)
    {
	    cout << " " << VectorBLocal[i];
	}
    cout << endl;

    // Calculo de la multiplicacion escalar entre vectores
    producto = 0;
    for (int i = 0; i < TAMANIO; i++)
    {
        producto += VectorALocal[i] * VectorBLocal[i];
    }
 
 	/*
       Reunimos los datos en un solo proceso, aplicando una operacion
       aritmetica, en este caso, la suma.
    */
    MPI_Reduce(
        &producto,        //Elemento a enviar (cada proceso la enviará)
        &total,           //Variable donde se almacena la reunion de los datos
        1,                //Cantidad de datos a reunir
        MPI_INT,          //Tipo del dato que se reunira
        MPI_SUM,          //Operacion aritmetica a aplicar
        0,                //Proceso que recibira los datos
        MPI_COMM_WORLD);  //Comunicador a utilizar, el global
 
    if (rank == 0)
    {
    	cout << "Se imprime vector A:" << endl;
        for(int i = 0; i < elementos_vector; i++)
        {
		    cout << " " << VectorA[i];
	    }
        cout << endl;
        cout << "Se imprime vector B:" << endl;
        for(int i = 0; i < elementos_vector; i++)
        {
		    cout << " " << VectorB[i];
	    }
        cout << endl;
        cout << "La suma total es: " << total << endl;
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

