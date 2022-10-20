#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, buzon, tamanio;
    MPI_Status estado;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tamanio);

    //Envio de mensajes
    if (rank==0) {
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }
    else {
        //Recepción de mensajes
        MPI_Recv(&buzon,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&estado);
        cout<< "Soy el proceso "<<rank<<" y he recibido "<<buzon<<endl;
        if (rank< tamanio -1)
            MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}