#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
#define N 5
int main(int argc, char *argv[])
{
    int rank, size, cantMult, multMax;
    multMax = 0;
    MPI_Init(&argc, &argv); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    vector<int>  VecGeneral;
    VecGeneral.resize(size*N, 0);

    if(rank==0){ //Proceso Raíz
        //Se rellena el VecGeneral con números pseudoaleatorios
        for (int i = 0; i < VecGeneral.size(); i++){
            VecGeneral[i] = rand() % 100;            
        }

        cout << "Vector Inicial: ";
        cout<< "[";
        for (int i = 0; i < VecGeneral.size()-1; i++){
            cout<< VecGeneral[i] << ", ";
        }
        cout << VecGeneral[VecGeneral.size()-1] << "]" << endl;
    }
    
    // Se envía el VecGeneral cargado a todos los procesos
    MPI_Bcast(&VecGeneral[0], size*N, MPI_INT, 0, MPI_COMM_WORLD);
    cantMult = 0;

    // Por cada proceso se verifica que sean múltiplo del elemento en la posición "rank"
    for (int i = 0; i < VecGeneral.size(); i++){
        cantMult += (VecGeneral[i] % VecGeneral[rank]==0) ? 1 : 0;
    }


    cout<< "El proceso "<<rank << " verifica que el número en su posición (" << VecGeneral[rank]<<") tiene "<< cantMult << " múltiplo/s"<< endl;

    MPI_Reduce(&cantMult, &multMax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if(rank == 0)
        cout<<"La mayor cantidad de múltiplos que tuvo un proceso fue: " << multMax <<endl;
    
    MPI_Finalize();
    
    return 0;

}