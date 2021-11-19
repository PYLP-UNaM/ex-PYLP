
#include "mpi.h"
#include <iostream>
using namespace std;
 
int main(int argc, char *argv[])
{
    int rank, size, n, lng, producto, sumaGlobal;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    n = 5;
    producto =0;
    sumaGlobal=  0;
    lng = size*5;

    int vector1[lng];
    int vector2[lng];
    int vector1Aux[n];
    int vector2Aux[n];

    if(rank == 0) {

        for(int i = 0; i < lng ; i++){
            vector1[i] = i;
            vector2[i] = i * i+1;
        }
        printf("Primer array: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", vector1[i]);
            
        }
        printf("\nSegundo array: \n");
        for(int i = 0; i<lng ; i++){
            printf("%d - ", vector2[i]);
        }
        printf("\n");
    }
    // distribuir el vector Dos con MPI_Scatter
    MPI_Scatter(
        &vector2[0],  //Dirección inicial del buffer de salida
        n,                     //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,                 //Tipo de dato que se va a enviar
        &vector2Aux[0],      //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        n,                     //Número de elementos que espera recibir cada proceso
        MPI_INT,                 //Tipo de datos de los elementos a recibir 
        0,                       //Rango del proceso que hace el envio
        MPI_COMM_WORLD           //Comunicador por el que realizar la comunicación.
    );
// distribuir el vector uno con MPI_Scatter
    MPI_Scatter(
        &vector1[0],    //Dirección inicial del buffer de salida
        n,                       //Número de elementos que se envía a cada proceso del comunicador
        MPI_INT,                   //Tipo de dato que se va a enviar
        &vector1Aux[0],        //Direción del buffer de recepción (para todos los procesos, incluido el proceso raíz).
        n,                       //Número de elementos que espera recibir cada proceso
        MPI_INT,                   //Tipo de datos de los elementos a recibir 
        0,                         //Rango del proceso que hace el envio
        MPI_COMM_WORLD             //Comunicador por el que realizar la comunicación.
    );


    // operar con los vectores locales
    for (int i = 0; i < n; i++){

        producto += vector1Aux[i] * vector2Aux[i];
        
    }

    // se reduce (por suma) en la variable sumaGlobal el resultado de los productos locales
    MPI_Reduce(
        &producto,   //Dirección inicial del buffer en envío.
        &sumaGlobal,   //Dirección inicial del buffer de recepción, útil únicamente para el proceso raíz.
        1,            //Número de elementos que se va a enviar
        MPI_INT,      //Tipo de datos de los elementos del buffer de envío
        MPI_SUM,      //Operación de reducción
        0,            // Rango del proceso raíz - receptor
        MPI_COMM_WORLD //Comunicador por el que se realiza la comunicación.
    );

    if (rank == 0) { // El proceso 0 informa el resultado
        
        cout<<"\nEl resultado del producto escalar es: "<<sumaGlobal<<endl;
    }

    MPI_Finalize();
    
    return 0;
}
