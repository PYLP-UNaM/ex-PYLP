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
    }
    printf("\n\n");

    // Repartimos los valores del vector principal 
    MPI_Scatter(
        &Vector,                 // Valores a dividir y compartir con cada proceso
        elementos_vector / size, // Cantidad que se envia a cada proceso
        MPI_INT,                 // Tipo del dato que se enviara
        &VectorLocal,            // Variable donde recibir los datos
        elementos_vector / size, // Cantidad que recibe cada proceso
        MPI_INT,                 // Tipo del dato que se recibira
        0,                       // proceso principal que reparte los datos
        MPI_COMM_WORLD);         // Comunicador (En este caso, el global)
 
    
    printf("\n");
    printf("Datos vector proceso (%i): ",rank);
    for(int i=0;i<elementos_vector/size;i++){
	    printf("%i - ",VectorLocal[i]);
	}
    
    printf("\n");

    int Vector_por_proceso[tamanio];
    // Calculamos para cada elemento del vector si es multiplo del nº de proceso + 2
    for (int i = 0; i < tamanio; ++i) {
        //si el nº de rank + 2 es igual a 0 entonces escribimos un 1 (uno) en el vector resultado sino un 0 (cero)
        Vector_por_proceso[i] = VectorLocal[i] % (rank + 2) == 0 ? 1 : 0;
    }
    
 
    // Gather reune todos los vectores enviados por cada proceso, solamente lo unimos todo
    MPI_Gather(
        &Vector_por_proceso,//Elemento a enviar (cada proceso la enviará es un vector)
        tamanio,            //Cantidad de elementos a enviar (tamaño del vector)  
        MPI_INT,            //Tipo de dato de lo que se enviará
        &VectorResultado,   //En donde se reciben los elementos (vector con tamaño igual al repartido con MPI_Scatter)
        tamanio,            //Cantidad de elementos a recibir
        MPI_INT,            //Tipo de dato de lo que se va a recibir
        0,                  //Proceso que recibira los datos
        MPI_COMM_WORLD);    //Comunicador a utilizar el global
 
    //El proceso raiz imprime todo el vector resultado con los 0 (ceros) y 1 (unos)
    if (rank == 0){
        printf("\n");
        for(int i=0;i<elementos_vector;i++){
            printf("%i\t",VectorResultado[i]);
        }    
    }
        
    

	// Terminamos la ejecucion de los procesos, despues de esto solo existira
	// el proceso 0
	// ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
	// de codigo despues de "Finalize", es conveniente asegurarnos con una
	// condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();
    return 0;
}