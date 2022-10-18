#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank ;
    
    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    if((rank % 2) == 0){
        printf("Soy el proceso %d, un proceso par. \n", rank); 
    }else{
        printf("Soy el proceso %d, un proceso impar. \n", rank);
    }

    MPI_Finalize();

    return 0;
}
