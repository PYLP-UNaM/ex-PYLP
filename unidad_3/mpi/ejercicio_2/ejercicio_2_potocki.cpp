#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv); // inicia
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // obtiene el ID del proceso 
    
    if (rank % 2 == 0) { // si es par
        cout<<"soy el proceso: "<<rank<<" un proceso par"<<endl;
    } else {
        cout<<"soy el proceso: "<<rank<<" un proceso impar"<<endl;
    }

 
    MPI_Finalize(); // finaliza 

    return 0;
}