#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rango, size, lng;
    int multiplos[2];       //posicion 0 el rango del proceso y posicion 1 el numero de multiplos que tiene
    int resMultiplos[2];    //posicion 0 el rango del proceso y posicion 1 el numero de multiplos que tiene
    multiplos[0] = 4535;
    multiplos[1] = 0;
    resMultiplos[0] = 5335;
    resMultiplos[1] = 0;
    MPI_Init(&argc, &argv); //Inicializamos la estructura de comunicación paralela entre procesos

    MPI_Comm_rank(MPI_COMM_WORLD, &rango); //Obtenemos (en rango) el rango del comunicador global que es MPI_COMM_WORLD
    MPI_Comm_size(MPI_COMM_WORLD, &size); //Obtenemos (en size) el tamaño del comunicador MPI_COMM_WORLD

    //Definimos el vector y su tamaño
    lng = size * 5;

    int vectorGlobal[lng];


    //El proceso 0 carga del vector
    if (rango == 0){
        for (int i = 0; i < lng; i++){
            vectorGlobal[i] = i+1;

        }
        //Imprimo el vector global
        printf("Vector Global \n");
        for (int i = 0; i < lng; i++){
            printf("%d - ",vectorGlobal[i]);
        }
        printf("\n");  
    }

    //Se envia el vector global a todos los procesos
    MPI_Bcast(
        &vectorGlobal[0],   //La variable que se transmite
        lng,                //Tamaño de lo que se envia
        MPI_INT,            //Tipo de datos
		0,                  //Rango del proceso que transmitira
        MPI_COMM_WORLD      //Por cual comunicador se hace la transmisión
    );

    //Imprimo el vector que recibió cada proceso
    printf("Soy el proceso proceso %d y recibí este vector: \n",rango);
    for (int i = 0; i < lng; i++){
        printf("%d - ",vectorGlobal[i]);
    }
    printf("\n"); 

    //Contamos los multiplos de la posicion del vector segun el rango del vector
    for (int i = 0; i < lng; i++){
        if (vectorGlobal[i] % vectorGlobal[rango] == 0){
            multiplos[0] = rango;
            multiplos[1]++;
        }
    }

    //Imprimo la cantidad de multiplos
    printf("Multiplos del elemento en la posicion %d: %d\n", rango, multiplos[1]);

    //Mandamos la cantidad de multiplos para que MPI_Reduce elija el que mas multiplos tuvo
    MPI_Reduce(
        &multiplos[1],          //Lo que envio 
        resMultiplos,           //Donde lo recibo
        1,                      //Tamaño de lo que envio
        MPI_INT,                //Tipo de lo que se envia (reduce)
        MPI_MAX,                //Operacion que se realiza
        0,                      //Proceso receptor
        MPI_COMM_WORLD          //Comunicador
    );

    //Imprimimos en el proceso 0 cual fue el que mas multiplos
    if (rango == 0){
        printf("El proceso que mas multiplos obtuvo fue %d con %d múltiplos\n", resMultiplos[1], resMultiplos[0]);
    }

    MPI_Finalize();
}