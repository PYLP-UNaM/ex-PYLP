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
 
     
    // Creacion y relleno del vector principal
    int elementos_vector = tamanio * size; //cantidad de elementos del vector principal
    
    int Vector[elementos_vector]; //vector principal a ser repartido
    int VectorResultado[elementos_vector]; //vector donde se almacenarán los datos recibidos por cada proceso
    int VectorLocal[tamanio];     //vector local para cada proceso
    

    srand(time(NULL));

    if (rank == 0) {
        for (int i = 0; i < elementos_vector; ++i) {
            Vector[i] = 1+rand()%((50+1)-1); // Vector recibe valores aleatorios entre 1 y 50
        }
        printf("\n\n");
        printf("Imprimimos los elementos del vector \n");
        for(int i=0;i<elementos_vector;i++){
		    printf("%i - ",Vector[i]);
	    }

        // Enviamos el vector a todos los procesos 
    }

    MPI_Bcast(
            &Vector,                 // Variable a enviar a cada proceso
            elementos_vector,        // Cantidad que se envia a cada proceso
            MPI_INT,                 // Tipo del dato que se enviara
            0,                       // proceso principal que reparte los datos
            MPI_COMM_WORLD);         // Comunicador (En este caso, el global)
    

    
 
    
       
    printf("\n");

    
    // Calculamos para cada elemento del vector si es multiplo del nº de proceso + 2
    int n=0;
    int valor_rank=Vector[rank];
    for (int i = 0; i < elementos_vector; ++i) {
        //si el nº de rank + 2 es igual a 0 entonces escribimos un 1 (uno) en el vector resultado sino un 0 (cero)
        
        if (Vector[i] % (valor_rank) == 0){
            n++;
        } 
    }
    printf("Proceso %i - Cantidad de valores multimos de %i son %i\n",rank,Vector[rank], n);



     // Reunimos los datos en un solo proceso, aplicando una operacion
    // aritmetica, en este caso, la suma.
    int total;
    MPI_Reduce(
        &n,               //Elemento a enviar (cada proceso la enviará)
        &total,           //Variable donde se almacena la reunion de los datos
        1,                //Cantidad de datos a reunir
        MPI_INT,          //Tipo del dato que se reunira
        MPI_MAX,          //Operacion aritmetica a aplicar
        0,                //Proceso que recibira los datos
        MPI_COMM_WORLD);  //Comunicador a utilizar el global
 
    if (rank == 0){
        printf("\n");
        printf("La mayor cantidad de multiplos obtenido por un proceso fue de: %i \n",total);
    }


	// Terminamos la ejecucion de los procesos, despues de esto solo existira
	// el proceso 0
	// ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
	// de codigo despues de "Finalize", es conveniente asegurarnos con una
	// condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();
    return 0;
}