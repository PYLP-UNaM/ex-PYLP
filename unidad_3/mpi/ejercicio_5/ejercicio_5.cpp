#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, num;

    // Se inicia la comunicación paralela entre procesos
    MPI_Init(&argc, &argv);  

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD

    num = 5;
    lng = size * num;
    int vectorPrincipal[lng];
    int vectorLocal[num];

    // Se carga el vector en el proceso 0
    if (rank == 0){

        for (int i = 0; i < lng; i++){
            vectorPrincipal[i] = rand() % 100;
        }

        // imprimir el vector
        printf("Vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipal[i]);
        }

        printf("\n\n");
    }

    // Distribuir el vector  con MPI_Scatter
    MPI_Scatter(
      &vectorPrincipal[0],       // Dirección inicial del buffer de salida
      num,                       // Número de elementos que se envía a cada proceso del comunicador
      MPI_INT,                   // Tipo de dato que se va a enviar
      &vectorLocal[0],           // Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
      num,                       // Número de elementos que espera recibir cada proceso
      MPI_INT,                   // Tipo de datos de los elementos a recibir 
      0,                         // Rango del proceso que hace el envio
      MPI_COMM_WORLD             // Comunicador por el que realizar la comunicación.
      );


    // Operar los vectores locales
    // Cada posicion del vector local es cambiada por 1 o 0
    // Si el numero es multiplo de "rango + 2" se reemplaza por 1, de lo contrario 0
    for (int i = 0; i < num; i++){
        if (vectorLocal[i] % (rank + 2) == 0){
            vectorLocal[i] = 1;
        } else {
            vectorLocal[i] = 0;
        }
    }

    // Se unen los vectores locales en el proceso 0 con MPI_Gather
    MPI_Gather(
        &vectorLocal[0],         // Dirección inicial del buffer de envío
        5,                       // Número de elementos que va a enviar cada proceso individualmente
        MPI_INT,                 // Tipo de dato de cada elemento del buffer de envío
        &vectorPrincipal[0],     // Dirección inicial del buffer de recepción (útil solamente para el proceso raíz).
        5,                       // Número de elementos que se espera recibir de cada uno de los procesos
        MPI_INT,                 // Tipo de dato que se espera recibir en el buffer de entrada
        0,                       // Rango del proceso raíz (el proceso receptor)
        MPI_COMM_WORLD           // Comunicador por el que se realiza la transferencia de datos
        );


    if (rank == 0) { // El proceso 0 informa el resultado
        printf("El resultado es el siguiente vector: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -",vectorPrincipal[i]); 
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
} 