#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
      int rank, buzon, tamanio;
      MPI_Status estado;

      MPI_Init(&argc, &argv); // Se inicia el entorno MPI 
      MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Se obtiene la identificación del proceso en el comunicador global
      MPI_Comm_size(MPI_COMM_WORLD, &tamanio); // Se obtiene el número de procesos en el comunicador global

      //Envio de mensajes: el proceso con id 0 envía un mensaje al proceso 2
      if (rank==0) {
          MPI_Send(&rank, // Proceso emisor
                      1,  // Tamaño del vector a enviar
                      MPI_INT, // Tipo de dato que se envía
                      rank+1,  // Proceso receptor
                      0,       // Tag
                      MPI_COMM_WORLD); // Comunicador
      }
      else {
          // Recepción de mensajes: los procesos (excepto en id=0 e id=tamanio) reciben mensaje del proc id-1
          // y envían al proc id+1
          MPI_Recv(&buzon, // Referencia - vector donde se almacena lo recibido
                      1,   // Tamaño del vector a recibir
                      MPI_INT, // Tipo de dato recibido
                      rank-1,  // id proceso del que se recibe el mensaje
                      0,       // Tag
                      MPI_COMM_WORLD, // Comunicador
                      &estado); // Referencia - información estado de recepción
          cout<< "Soy el proceso "<<rank<<" y he recibido "<<buzon<<endl;
          // Se controla el proceso con id más alto (último proceso), y solo recibe mensaje
          if (rank< tamanio -1)
              MPI_Send(&rank,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
      }
      // Finaliza la ejecución de los procesos
      MPI_Finalize();
      return 0;
}