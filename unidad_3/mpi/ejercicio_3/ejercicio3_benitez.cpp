  
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, buzon;
    MPI_Status estado;
 
    // Se inicia la comunicación paralela entre procesos
    MPI_Init(&argc, &argv); 

    // Se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size);  
    
    // Se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  

    //El proceso con ID 0, envia un msj al proceso 2
    if(rank == 0){ 

        MPI_Send(
                    &rank,          // Proceso que envia
                    1,              // Tamaño del vector a enviar
                    MPI_INT,        // Tipo de dato que se envia
                    rank+1,         // Proceso que recibe
                    0,              // Etiqueta
                    MPI_COMM_WORLD  // Comunicador por donde se envia el msj
                    );

    }else{

        // Los procesos (exepto el de ID 0 y ID nSize) reciben msj del proceso n-1, y envia msj al proceso n+1
        if(rank != size-1){ 
            MPI_Recv(
                &buzon,         // Referencia al vector donde se almacena lo recibido
                1,              // Tamaño del vector a recibir
                MPI_INT,        // Tipo de dato que se recibe
                rank-1,         // Proceso desde el cual se recibe el msj
                0,              // Etiqueta
                MPI_COMM_WORLD, // Comunicador por donde se recibe el msj
                &estado         // Informacion sobre el estado de la recepcion (si ocurrio un error)
                );

            MPI_Send(
                    &rank,          // Proceso que envia
                    1,              // Tamaño del vector a enviar
                    MPI_INT,        // Tipo de dato que se envia
                    rank+1,         // Proceso que recibe
                    0,              // Etiqueta
                    MPI_COMM_WORLD  // Comunicador por donde se envia el msj
                    );

            printf("Soy el proceso %d y he recibido el mensaje: %d\n", rank, buzon);

        }else{ 
            // El proceso (ultimo) con ID mas alto, solo recibe un msj
            MPI_Recv(
                &buzon,             // Referencia al vector donde se almacena lo recibido
                1,                  // Tamaño del vector a recibir
                MPI_INT,            // Tipo de dato que se recibe
                rank-1,             // Proceso desde el cual se recibe el msj
                0,                  // Etiqueta
                MPI_COMM_WORLD,     // Comunicador por donde se recibe el msj
                &estado             // Informacion sobre el estado de la recepcion (si ocurrio un error)
                );

            printf("Soy el proceso %d y he recibido el mensaje: %d\n", rank, buzon);

        }
    }
  
    // Se finaliza la comunicación paralela entre procesos
    MPI_Finalize(); 
    
    return 0;
}