/* hacer un programa que lance `X` procesos, segun si su numero de rango sea par o impar, deberan imprimir:

   ```c++
   # procesos pares
   cout<<"soy el proceso: "<<rank<<" un proceso par"<<endl;

   # procesos impares
   cout<<"soy el proceso: "<<rank<<" un proceso impar"<<endl;
   ``` */

#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank % 2 == 0)
    {
        cout << "soy el proceso: " << rank << " un proceso par" << endl;
    }
    else
    {
        cout << "soy el proceso: " << rank << " un proceso impar" << endl;
    }
    MPI_Finalize();
    return 0;
}