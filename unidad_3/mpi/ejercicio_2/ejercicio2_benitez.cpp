#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank;

    MPI_Init(&argc, &argv); //se inicia la comunicación paralela entre procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD

    //segun el numero que tenga como identificador el proceso, se analiza si es par o impar; y segun esto imprime un mensaje.
    if(rank % 2 == 0){

        printf("Soy el proceso:  %d, y soy un proceso Par \n", rank);

    }else{

        printf("Soy el proceso:  %d, y soy un proceso Impar \n", rank);

    }

    MPI_Finalize(); //se finaliza la comunicación paralela entre procesos

    return 0;
}