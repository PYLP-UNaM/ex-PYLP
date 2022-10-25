#include "mpi.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  int rank, size, mensaje, buzon, new_mensaje;

  mensaje = 999;

  MPI_Status estado;

  MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

  MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global

  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

  cout << "¡Hola Mundo desde el proceso " << rank << " de " << size << " que somos!" << endl;

  if (rank == 0)
  {
    MPI_Send(&mensaje, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    cout << "Proceso " << rank << " envia " << mensaje << " al proceso " << rank + 1 << endl;
  }
  else
  {
    MPI_Recv(&buzon // Referencia al vector donde se almacenara lo recibido
             ,
             1 // numero de elementos máximo a recibir
             ,
             MPI_INT // Tipo de dato que recibe
             ,
             MPI_ANY_SOURCE // pid del proceso origen de la que se recibe
             ,
             MPI_ANY_TAG // etiqueta
             ,
             MPI_COMM_WORLD // Comunicador por el que se recibe
             ,
             &estado); // estructura informativa del estado
    cout << "Proceso " << rank << " recibe " << buzon << " del proceso " << estado.MPI_SOURCE << endl;
    new_mensaje = buzon + 1;

    if (rank < size - 1)
      MPI_Send(&new_mensaje, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
  }

  // Terminamos la ejecucion de los procesos, despues de esto solo existira
  // la hebra 0
  // ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
  // de codigo despues de "Finalize", es conveniente asegurarnos con una
  // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
  MPI_Finalize();

  return 0;
}