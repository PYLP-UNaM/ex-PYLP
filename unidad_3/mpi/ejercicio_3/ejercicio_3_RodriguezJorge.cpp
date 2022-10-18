#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank,id,size; 
    MPI_Status status; 

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    if(rank == 0)
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    else
        MPI_Recv(&id,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
    
    if(rank < size-1)
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);

    printf("Soy el Proceso %d y he recibido %d", rank, id); 
    
    MPI_Finalize();
    return 0;
}