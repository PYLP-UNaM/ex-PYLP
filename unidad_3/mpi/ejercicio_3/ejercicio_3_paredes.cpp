/* escribir un programa paralelo que encadene el envío y recepción de un mensaje, mensaje sera el rango (identificador) del proceso que envía.

   el proceso sero debe enviar su nro. de rango al segundo, el segundo recibirá dicho mensaje y enviará otro al tercero, y así sucesivamente para todos los procesos lanzados.

   Todo proceso que reciba un mensaje debe imprimirlo de la siguiente manera:

   ```
   "Soy el proceso X y he recibido M",
   ```

   siendo X el rango del proceso y M el mensaje recibido. */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rank, size, tag = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int i;
    int mensaje;

    if (rank == 0)
    {
        MPI_Send(&rank, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);
        printf("Soy el proceso %d y he recibido %d\n", rank, mensaje);
    }
    else
    {
        MPI_Recv(&mensaje, 1, MPI_INT, rank - 1, tag, MPI_COMM_WORLD, &status);
        printf("Soy el proceso %d y he recibido %d\n", rank, mensaje);
        if (rank == size - 1)
        {
            MPI_Send(&rank, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        }
        else
        {
            MPI_Send(&rank, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}