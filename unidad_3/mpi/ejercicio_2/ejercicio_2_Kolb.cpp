#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
    {
        int rank, size;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);


        if(rank%2==0){
            cout<<"soy el proceso: "<<rank<<" un proceso par"<<endl;
        }else{
            cout<<"soy el proceso: "<<rank<<" un proceso impar"<<endl;
        }

        MPI_Finalize();
        return 0;
}