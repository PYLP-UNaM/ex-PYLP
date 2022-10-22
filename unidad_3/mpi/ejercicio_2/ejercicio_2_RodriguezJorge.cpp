#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank ;
    
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    // Si el id del proceso es par, se imprime...
    if((rank % 2) == 0){
        printf("Soy el proceso %d, un proceso par. \n", rank); 
    }
    // Si el id del proceso es impar, se imprime... 
    else{
        printf("Soy el proceso %d, un proceso impar. \n", rank);
    }

    MPI_Finalize(); // Se finaliza la ejecución de los procesos

    return 0;
}
