#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 
    printf("Soy el proceso %d, de %d que somos!!! Saludos! \n", rank, size) ;
 
    MPI_Finalize();
    
    return 0;
}