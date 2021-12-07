#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, n, lng, sumaLocal, sumaTotal;
 
    MPI_Init(&argc, &argv); // Inicializacion MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // numero de procesos 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // identificacion de nuestro proceso en el comunicador global

    n = 5;
    sumaLocal =0;
    sumaTotal=  0;
    lng = size*5;

    int v1[lng];
    int v1Local[n];

    if(rank == 0) {

        for(int i = 0; i < lng ; i++){
            v1[i] = i;
        }
        printf("Vector Global: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", v1[i]);
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

    // operar con los vectores locales
    for (int i = 0; i < n; i++){

        if((v1Local[i] % (rank+2) ) == 0){
            v1Local[i] = 1; 
        }else {
            v1Local[i] = 0;
        }
        
    }

    //Se unen los vectores locales en el proceso 0 con MPI_Gather
    MPI_Gather(
        &v1Local[0],         // Dirección inicial del buffer de envío
        5,                       // Número de elementos que va a enviar cada proceso individualmente
        MPI_INT,                 // Tipo de dato de cada elemento del buffer de envío
        &v1[0],     // Dirección inicial del buffer de recepción (útil solamente para el proceso raíz).
        5,                       // Número de elementos que se espera recibir de cada uno de los procesos
        MPI_INT,                 // Tipo de dato que se espera recibir en el buffer de entrada
        0,                       // Rango del proceso raíz (el proceso receptor)
        MPI_COMM_WORLD           // Comunicador por el que se realiza la transferencia de datos
    );

    
    if (rank == 0) { // El proceso 0 informa el resultado

        printf("Resultado del vector transformado: \n");
        for (int i = 0; i < lng; i++){
            printf(" %d -",v1[i]); 
        }
        printf("\n");
    }


    MPI_Finalize();
    
    return 0;
}