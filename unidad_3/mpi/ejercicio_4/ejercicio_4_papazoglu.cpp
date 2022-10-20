
#include "mpi.h"
#include <iostream>
#include <time.h>
using namespace std;

#define tamanio 5

 
int main(int argc, char *argv[]) 
{
    int result, rank, size;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
     
    // Creacion y relleno de los vectores
    int elementos_vector = tamanio * size; //cantidad de elementos de los vectores principales
    
    int VectorA[elementos_vector]; //vector principal A
    int VectorB[elementos_vector]; //vector principal B
    int VectorALocal[tamanio];     //vector local A para cada proceso
    int VectorBLocal[tamanio];      //vector local B para cada proceso

    srand(time(NULL));





    if (rank == 0) {
        for (int i = 0; i < elementos_vector; ++i) {
            VectorA[i] = 1+rand()%((50+1)-1); // Vector A recibe valores aleatorios entre 1 y 50
            VectorB[i] = 1+rand()%((100+50)-1); // Vector B recibe valores aleatorios entre 50 y 100
        }
        printf("\n\n");
        printf("Imprimimos vector A \n");
        for(int i=0;i<elementos_vector;i++){
		    printf("%i - ",VectorA[i]);
	    }


        printf("\n\n");
        printf("Imprimimos vector B \n");
        for(int i=0;i<elementos_vector;i++){
		    printf("%i - ",VectorB[i]);
	    }




    }
    printf("\n\n");

    // Repartimos los valores del vector A
    MPI_Scatter(
        &VectorA,                // Valores a dividir y compartir con cada proceso
        elementos_vector / size, // Cantidad que se envia a cada proceso
        MPI_INT,                 // Tipo del dato que se enviara
        &VectorALocal,           // Variable donde recibir los datos
        elementos_vector / size, // Cantidad que recibe cada proceso
        MPI_INT,                 // Tipo del dato que se recibira
        0,                       // proceso principal que reparte los datos
        MPI_COMM_WORLD);         // Comunicador (En este caso, el global)

    // Repartimos los valores del vector B
    MPI_Scatter(
        &VectorB,
        elementos_vector / size,
        MPI_INT,
        &VectorBLocal,
        elementos_vector / size,
        MPI_INT,
        0,
        MPI_COMM_WORLD);
 
    
    printf("\n");
    printf("Datos vector A del proceso (%i): ",rank);
    for(int i=0;i<elementos_vector/size;i++){
	    printf("%i - ",VectorALocal[i]);
	}

    printf("\n");
    printf("Datos vector B del proceso (%i): ",rank);
    for(int i=0;i<elementos_vector/size;i++){
	    printf("%i - ",VectorBLocal[i]);
	}
    printf("\n");



    
    // Calculo de la multiplicacion escalar entre vectores
    int producto = 0;
    for (int i = 0; i < elementos_vector / size; ++i) {
        producto = producto + VectorALocal[i] * VectorBLocal[i];
    }
    int total;
 
    // Reunimos los datos en un solo proceso, aplicando una operacion
    // aritmetica, en este caso, la suma.
    MPI_Reduce(
        &producto,        //Elemento a enviar (cada proceso la enviará)
        &total,           //Variable donde se almacena la reunion de los datos
        1,                //Cantidad de datos a reunir
        MPI_INT,          //Tipo del dato que se reunira
        MPI_SUM,          //Operacion aritmetica a aplicar
        0,                //Proceso que recibira los datos
        MPI_COMM_WORLD);  //Comunicador a utilizar el global
 
    if (rank == 0){
        printf("\n");
        printf("La suma total es: %i\n",total);
    }
        
    

	// Terminamos la ejecucion de los procesos, despues de esto solo existira
	// el proceso 0
	// ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
	// de codigo despues de "Finalize", es conveniente asegurarnos con una
	// condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();
    return 0;
}
	
	
