#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, num, cantMultiplos, maxGlobal;

    // Se inicia la comunicación paralela entre procesos
    MPI_Init(&argc, &argv);  

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD

    num = 5;
    maxGlobal = 0;
    cantMultiplos = 0;
    lng = size * num;
    int vectorPrincipal[lng];

    // Se carga el vector en el proceso 0
    if (rank == 0){

        for (int i = 0; i < lng; i++){
            vectorPrincipal[i] = rand() % 100;
        }

        // Imprimir el vector
        printf("Vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipal[i]);
        }

        printf("\n\n");
    }

    // Se envia el vector cargado a todos los procesos
    MPI_Bcast(
        &vectorPrincipal[0],    // Dirección inicial del buffer desde donde se envia
        lng,                    // Número de elementos en el buffer
        MPI_INT,                // Tipo de dato de los elementos del buffer
		0,                      // Rango del proceso desde donde se transmitira
        MPI_COMM_WORLD          // Por que comunicador se hace la transmisión
    );
    
    // Operacion a realizar en cada proceso
    // Se contabiliza todos los elementos del vector, que sean multiplo del elemento en la posicion "rank"
    for (int i = 0; i < lng; i++){
        if (vectorPrincipal[i] % vectorPrincipal[rank] == 0){
            cantMultiplos ++;
        }
    }

    // Cada proceso informa su cantidad de numeros multiplos encontrados
    printf("Soy proceso %d; encontre %d multiplos del elemento %d\n", rank, cantMultiplos, vectorPrincipal[rank]);


    //Se obtiene en el proceso 0 la cantidad maxima de multiplos encontrados por un proceso
    MPI_Reduce(
            &cantMultiplos,     // Dirección inicial del buffer en envío.
            &maxGlobal,         // Dirección inicial del buffer de recepción, útil únicamente para el proceso raíz.
            1,                  // Número de elementos que se va a enviar
            MPI_INT,            // Tipo de datos de los elementos del buffer de envío
            MPI_MAX,            // Operación de reducción
            0,                  // Rango del proceso raíz - receptor
            MPI_COMM_WORLD      // Comunicador por el que se realiza la comunicación.
            );


    if (rank == 0) { // El proceso 0 informa el resultado
        printf("La mayor cantidad de multiplos obtenidos por un proceso es: %d \n", maxGlobal);
    }

    MPI_Finalize(); // Se finaliza la comunicación paralela entre procesos

    return 0;
}