#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, mensaje;
    MPI_Status estado;

    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 
    cout<<"¡Proceso "<<rank<<" de "<<size<<" que somos!"<<endl;
 
    if(rank == 0){
        MPI_Send(
            &rank, //mando
            1, // tamanio de lo que envio
            MPI_INT, //tipo de dato
            rank+1, // identificador del destino
            0, 
            MPI_COMM_WORLD 
        );
    }else{
        MPI_Recv(
            &mensaje, //donde se almacena
            1, //tamanio de lo recibido
            MPI_INT, //ripo de dato
            rank-1, //de quien se espera el msj
            0, 
            MPI_COMM_WORLD, 
            &estado 
        );  
        printf("Proceso %d y he recibido %d \n", rank, mensaje);

        if(rank < size - 1){
            MPI_Send(
                &rank, //mando
                1, // tamanio de lo que envio
                MPI_INT, //tipo de dato
                rank+1, // identificador del destino
                0, 
                MPI_COMM_WORLD 
            );
        }
    }

    MPI_Finalize();
    
    return 0;