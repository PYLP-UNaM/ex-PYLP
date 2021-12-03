#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size,mensaje;
    MPI_Status estado;
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
 
   
  if(rank < size - 1){
    MPI_Send(&rank //referencia al vector de elementos a enviar
                ,1 // tamaño del vector a enviar
                ,MPI_INT // Tipo de dato que envias
                ,rank+1 // pid del proceso destino
                ,0 //etiqueta
                ,MPI_COMM_WORLD); //Comunicador por el que se manda
    }
    MPI_Recv(
            &mensaje, //donde se almacena lo recibido
            1, //tamanio de lo recibido
            MPI_INT, //ripo de dato de lo recibido
            rank-1, //de quien se espera el msj
            0, //etiqueta
            MPI_COMM_WORLD, //comunicador
            &estado //informacion
        ); 
      cout<<"Soy el proceso "<<rank<<" y he recibido "<<mensaje<<endl;
    MPI_Finalize();
    
    return 0;
}