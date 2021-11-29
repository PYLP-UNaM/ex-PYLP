#include "mpi.h"
#include <iostream>
using namespace std;

#define ROOT 0
#define SLICE 5

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv); // inicio del entorno MPI
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ID de proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // cantidad de procesos en el comunicador global
    
    // estructura para obtener rango y cantidad en el MPI_Reduce del proceso con mayor cantidad de multiplos
    struct { 
        int quantity;
        int   rank;
    } multiples, result;

    int vectorSize = size * SLICE;
    int vector[vectorSize];

    if (rank == ROOT) {
        // cargar v de forma aleatoria
        for (int i = 0; i < vectorSize; i++) {
            vector[i] = rand() % 100;
        }

        // imprimir v
        cout << endl;
        cout << "VECTOR: " << endl;
        for (int i = 0; i < vectorSize; i++) {
            cout << vector[i] << " - ";
        }
        cout << endl;
        
    }

    // Enviar a todos los procesos el vector
    MPI_Bcast(
        &vector,       // lo que se va a distribuir entre los procesos
        vectorSize,          // numero de elementos que se envia a cada proceso
        MPI_INT,        // tipo de dato de lo que se va a enviar
        ROOT,           // quien realiza el envio
        MPI_COMM_WORLD  // los procesos quienes particiban en la distribuicion
    );

    int partialResults[vectorSize];
    multiples.rank = rank;
    multiples.quantity = 0;
    int isMultiple;
    for (int i = 0; i < vectorSize; i++) {
        isMultiple = vector[i] % vector[rank] == 0 ? true : false;
        if (isMultiple){
            partialResults[multiples.quantity] = vector[i];
            multiples.quantity++;
        }
    }
    cout << endl;

    cout << endl;
    cout << "resultado parciales de " << rank << endl;
    for (int i = 0; i < multiples.quantity; i++) {
        cout << partialResults[i] << " - ";
    }
    cout << endl;

    MPI_Reduce(
        &multiples, // lo que se va emitir
        &result, // donde se va a recibir
        1,  // numero de elementos a emitir
        MPI_2INT, // tipo de dato de lo que se va emitir
        MPI_MAXLOC, // operacion de reduccion
        ROOT, // quien lo va a recibir
        MPI_COMM_WORLD // entre quienes se hace la reduccion
    );


    if (rank == ROOT) {
        cout << endl;
        cout << endl;
        cout << "el que tuvo mas multiplos fue: " <<endl;
        cout << "rango " << result.rank << " con " << result.quantity << " multiplos." <<endl;
        cout << endl;
        cout << endl;
    }


    MPI_Finalize();

    return 0;
}