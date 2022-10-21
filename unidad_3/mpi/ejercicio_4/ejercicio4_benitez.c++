#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, size, lng, sumaLocal, num, sumaTotal;

    // Se inicia la comunicación paralela entre procesos
    MPI_Init(&argc, &argv);  

    // Se obtiene en "size" el numero de procesos del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

    // Se obtiene en "rank" el identificador del proceso segun el comunicador MPI_COMM_WORLD
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

    num = 5;
    sumaLocal = 0;
    sumaTotal = 0;
    lng = size * num;
    int vectorPrincipalUno[lng];
    int vectorPrincipalDos[lng];
    int vectorLocalUno[num];
    int vectorLocalDos[num];

    // Se cargan los vectores en el proceso 0
    if (rank == 0){

        for (int i = 0; i < lng; i++){

            vectorPrincipalUno[i] = rand() % 100;
            vectorPrincipalDos[i] = rand() % 100;

        }

        // Imprimir los vectores generados
        printf("Primer vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipalUno[i]);
        }

        printf("\n");
        printf("Segundo vector cargado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -", vectorPrincipalDos[i]);
        }

        printf("\n\n");
    }

    // Distribuir el vector Uno con MPI_Scatter
    MPI_Scatter(
      &vectorPrincipalUno[0],    // Dirección inicial del buffer de salida
      num,                       // Número de elementos que se envía a cada proceso del comunicador
      MPI_INT,                   // Tipo de dato que se va a enviar
      &vectorLocalUno[0],        // Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
      num,                       // Número de elementos que espera recibir cada proceso
      MPI_INT,                   // Tipo de datos de los elementos a recibir 
      0,                         // Rango del proceso que hace el envio
      MPI_COMM_WORLD             // Comunicador por el que realizar la comunicación.
      );

    // Distribuir el vector Dos con MPI_Scatter
    MPI_Scatter(
      &vectorPrincipalDos[0],   // Dirección inicial del buffer de salida
      num,                      // Número de elementos que se envía a cada proceso del comunicador
      MPI_INT,                  // Tipo de dato que se va a enviar
      &vectorLocalDos[0],       // Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
      num,                      // Número de elementos que espera recibir cada proceso
      MPI_INT,                  // Tipo de datos de los elementos a recibir 
      0,                        // Rango del proceso que hace el envio
      MPI_COMM_WORLD            // Comunicador por el que realizar la comunicación.
      );

    // Operar los vectores locales
    for (int i = 0; i < num; i++){

        sumaLocal += vectorLocalDos[i] * vectorLocalUno[i];

    }

    // Se reduce (por suma) en la variable sumaTotal del proceso 0 el resultado de producto escalar segun la sumaLocal de los vectores
    MPI_Reduce(
            &sumaLocal,         // Dirección inicial del buffer en envío.
            &sumaTotal,         // Dirección inicial del buffer de recepción, útil únicamente para el proceso raíz.
            1,                  // Número de elementos que se va a enviar
            MPI_INT,            // Tipo de datos de los elementos del buffer de envío
            MPI_SUM,            // Operación de reducción
            0,                  // Rango del proceso raíz - receptor
            MPI_COMM_WORLD      // Comunicador por el que se realiza la comunicación.
            );

    
    // El proceso 0 informa el resultado
    if (rank == 0) { 

        printf("\nEl resultado del producto escalar es: %d\n", sumaTotal);


    }

    // se finaliza la comunicación paralela entre procesos
    MPI_Finalize();

    return 0;
} 