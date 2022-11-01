/** 
 * Crear un algoritmo que distribuya un vector *"Global"* de tamaño NP(cantidad de procesos lanzados) \* 5 entre los procesos lanzados `MPI_Scatter`. 

Cada proceso va a recibir los valores en un vector *"Local"* de tamaño 5. Cada proceso debe recorrer el vector y modificarlo escribiendo en cada posición, un 1 si el elemento de esa posición es multiplo del rango del proceso + 2  y un 0 si no lo es.

Luego todos los vectores *"Locales"* se unificarán en el proceso 0 `MPI_Gather`.
*/

#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *global = new int[size * 5];
    int *local = new int[5];

    if (rank == 0)
    {
        for (int i = 0; i < size * 5; i++)
        {
            global[i] = i;
        }
    }

    MPI_Scatter(global, 5, MPI_INT, local, 5, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < 5; i++)
    {
        if (local[i] % (rank + 2) == 0)
        {
            local[i] = 1;
        }
        else
        {
            local[i] = 0;
        }
    }

    MPI_Gather(local, 5, MPI_INT, global, 5, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < size * 5; i++)
        {
            cout << global[i] << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}


