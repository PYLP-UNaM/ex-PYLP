#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, contador,size;
    MPI_Status estado;
 
    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
 
    
    if(rank==0){
        //Envia mensajes
        MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }else{
        //Recibe mensajes
        MPI_Recv(&contador,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&estado);
        cout<< "Soy el proceso "<<rank<<" y he recibido "<<contador<<endl;

        //Envia mensaje pero controla no ser el ultimo antes
        if(rank<size-1){
            MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        }
    }
     
    
 
	
 
    MPI_Finalize();
    return 0;
}