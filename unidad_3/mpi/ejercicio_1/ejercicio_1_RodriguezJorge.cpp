#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv); // Se inicia el entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Se obtiene el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Se obtiene la identificacion de nuestro proceso en el comunicador global
 
    cout<<"¡Hola Mundo desde el proceso "<<rank<<" de "<<size<<" que somos!"<<endl;
 
    // Se termina la ejecucion de los procesos, después de esto solo existirá
    // la hebra 0
    // ¡Ojo! Esto no significa que los demás procesos no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar más codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();
    
    return 0;
}
