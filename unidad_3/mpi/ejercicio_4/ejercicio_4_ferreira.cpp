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

    int vectorSize = size * SLICE;
    int vector1[vectorSize];
    int vector2[vectorSize];
    int mailbox1[SLICE], mailbox2[SLICE]; // buzones para recibir los elementos
    int result;

    if (rank == ROOT) {
        // CARGAR VECTORES DE FORMA ALEATORIA
        for (int i = 0; i < vectorSize; i++) {
            vector1[i] = rand() % 100;
            vector2[i] = rand() % 100;
        }

        // IMPRIMIR VECTOR 1
        cout << endl;
        cout << "VECTOR " << "1: " << endl;
        for (int i = 0; i < vectorSize; i++) {
            cout << vector1[i] << " - ";
        }

        // IMPRIMIR VECTOR 2
        cout << endl;
        cout << "VECTOR " << "2: " << endl;
        for (int i = 0; i < vectorSize; i++) {
            cout << vector2[i] << " - ";
        }
        cout << endl;
    }

    MPI_Scatter(
        &vector1,       // lo que se va a distribuir entre los procesos
        SLICE,          // numero de elementos que se envia a cada proceso
        MPI_INT,        // tipo de dato de lo que se va a enviar
        &mailbox1,      // en donde cada proceso hace la recepcion
        SLICE,          // numero de elementos a recibir
        MPI_INT,        // tipo de dato de lo que se va a recibir
        ROOT,           // quien realiza el envio
        MPI_COMM_WORLD  // los procesos quienes particiban en la distribuicion
    );

    MPI_Scatter(
        &vector2,       // lo que se va a distribuir entre los procesos
        SLICE,          // numero de elementos que se envia a cada proceso
        MPI_INT,        // tipo de dato de lo que se va a enviar
        &mailbox2,      // en donde cada proceso hace la recepcion
        SLICE,          // numero de elementos a recibir
        MPI_INT,        // tipo de dato de lo que se va a recibir
        ROOT,           // quien realiza el envio
        MPI_COMM_WORLD  // los procesos quienes particiban en la distribuicion
    );

    cout << endl;
    cout << "MAIL BOX" << "1 de " << rank << endl;
    for (int i = 0; i < SLICE; i++) {
        cout << mailbox1[i] << " - ";
    }

    cout << endl;
    cout << "MAIL BOX" << "2 de " << rank << endl;
    for (int i = 0; i < SLICE; i++) {
        cout << mailbox2[i] << " - ";
    }
    cout << endl;

    int product = 0;
    cout << "SUMA de " << rank << ": ";
    for (int i = 0; i < SLICE; i++) {
        product = product + (mailbox1[i] * mailbox2[i]);
    }
    cout << product;
    cout << endl;

    MPI_Reduce(
        &product, // lo que se va emitir
        &result, // donde se va a recibir
        1,  // numero de elementos a emitir
        MPI_INT, // tipo de dato de lo que se va emitir
        MPI_SUM, // operacion de reduccion
        ROOT, // quien lo va a recibir
        MPI_COMM_WORLD // entre quienes se hace la reduccion
    );

    if (rank == ROOT) {
        cout << endl;
        cout << endl;
        cout << "RESULTADO: " << result;
        cout << endl;
    }

    MPI_Finalize();

    return 0;

    // Fixes #794
}
