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

    /* ANALISIS
        Vector global:          1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 -
        Multiplos del Proceso 0 (calcula el multiplo de 1): todos
        Multiplos del Proceso 1 (calcula el multiplo de 2): 2, 4, 6, 8, 10, 12, 14, 16, 18, 20
        
        Multiplos del Proceso 2 (calcula el multiplo de 3): 3, 6, 9, 12, 15, 18
        Multiplos del Proceso 3 (calcula el multiplo de 4): 4, 8, 14, 16, 20
        El proceso que mas multiplos tiene es el 0 porque 1 es multiplo de todos los numeros enteros
    */

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
        /*
            Vector Global
            1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 - 11 - 12 - 13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 - 
        */

    }

    //Se envia el vector global a todos los procesos
    MPI_Bcast(
        &vectorGlobal[0],   //La variable que se transmite
        lng,                //Tamaño de lo que se envia
        MPI_INT,            //Tipo de datos
		0,                  //Rango del proceso que transmitira
        MPI_COMM_WORLD      //Por cual comunicador se hace la transmisión
    );
