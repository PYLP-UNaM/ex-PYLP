#include "mpi.h"
#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;

    int rank, size,mensaje;
    
    MPI_Status estado; // Estado del proceso en MPI
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    if (rank < size - 1)
    {
	MPI_Send(&rank, //referencia al vector de elementos a enviar
                 1, // tamaño del vector a enviar
                 MPI_INT, // Tipo de dato que envias
                 rank+1, // pid del proceso destino
                 0, //etiqueta
                 MPI_COMM_WORLD //Comunicador por el que se manda
        );
    }
    if (rank)
    {
	MPI_Recv(&mensaje, //donde se almacena lo recibido
        	 1, //tamaño  recibido
        	 MPI_INT, //tipo de dato de lo recibido
        	 rank-1, //de quien se espera el msj
        	 0, //etiqueta
        	 MPI_COMM_WORLD, //comunicador
        	 &estado //informacion
        ); 
    	cout << "Soy el proceso " << rank << " y he recibido " << mensaje << endl;
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
