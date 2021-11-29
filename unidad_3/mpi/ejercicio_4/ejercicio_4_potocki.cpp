#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, n, lng, sumaLocal, sumaTotal;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    n = 5;
    sumaLocal =0;
    sumaTotal=  0;
    lng = size*5;

    int v1[lng];
    int v2[lng];
    int v1Local[n];
    int v2Local[n];

    if(rank == 0) {

        for(int i = 0; i < lng ; i++){
            v1[i] = i;
            v2[i] = i * i;
        }
        printf("Primer vector: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", v1[i]);
        }
        printf("\n Segundo vector: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", v2[i]);
        }
        printf("\n");
    }

    MPI_Scatter(
        &v1[0],    //Dirección inicial del buffer de salida
        n,                       //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,                   //Tipo de dato que se va a enviar
        &v1Local[0],        //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        n,                       //Número de elementos que espera recibir cada proceso
        MPI_INT,                   //Tipo de datos de los elementos a recibir 
        0,                         //Rango del proceso que hace el envio
        MPI_COMM_WORLD             //Comunicador por el que realizar la comunicación.
    );

    // distribuir el vector Dos con MPI_Scatter
    MPI_Scatter(
        &v2[0],  //Dirección inicial del buffer de salida
        n,                     //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,                 //Tipo de dato que se va a enviar
        &v2Local[0],      //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        n,                     //Número de elementos que espera recibir cada proceso
        MPI_INT,                 //Tipo de datos de los elementos a recibir 
        0,                       //Rango del proceso que hace el envio
        MPI_COMM_WORLD           //Comunicador por el que realizar la comunicación.
    );

    // operar con los vectores locales
    for (int i = 0; i < n; i++){

        sumaLocal += v1Local[i] * v2Local[i];
        
    }

    // se reduce (por suma) en la variable sumaTotal del proceso 0 el resultado de producto escalar segun la sumaLocal de los vectores
    MPI_Reduce(
        &sumaLocal,   //Dirección inicial del buffer en envío.
        &sumaTotal,   //Dirección inicial del buffer de recepción, útil únicamente para el proceso raíz.
        1,            //Número de elementos que se va a enviar
        MPI_INT,      //Tipo de datos de los elementos del buffer de envío
        MPI_SUM,      //Operación de reducción
        0,            // Rango del proceso raíz - receptor
        MPI_COMM_WORLD //Comunicador por el que se realiza la comunicación.
    );

    if (rank == 0) { // El proceso 0 informa el resultado
        printf("\nEl resultado del producto escalar es: %d\n", sumaTotal);
    }

    MPI_Finalize();
    
    return 0;
}