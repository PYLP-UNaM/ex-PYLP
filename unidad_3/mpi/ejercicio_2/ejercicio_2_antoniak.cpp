#include "mpi.h"
#include <iostream>
 
int main(int argc, char *argv[])
{
    using namespace std;

    int rank, size;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    if (rank % 2)
    {
        cout << "Soy el proceso: " << rank << " un proceso impar" << endl;
    }
    else
    {
        cout << "Soy el proceso: " << rank << " un proceso par" << endl;
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
