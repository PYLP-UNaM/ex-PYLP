#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    //inicializamos las variable a utilizar
    int rank, size, total, elementos;

    MPI_Init(&argc, &argv); // Inicialización del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el número de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificación de nuestro proceso en el comunicador global

    // cantidad de elementos por proceso que usaremos
    elementos = 5;
    // calculamos de la cantidad total que tendra nuestro arreglo principal
    total = size * elementos;

    // vectores principales
    float vector1[total], vector2[total];
    // defino los vectores locales donde cada proceso recibira los valores enviados por MPI_Scatter
    float vector1_local[elementos], vector2_local[elementos];

    // defino variables para realizar las operaciones requeridas
    float suma_parcial;                      // lo utilizará cada proceso en la suma local del mismo
    float sumas_parciales[size], suma_total; // El proceso raíz obtendrá los valores de todos los procesos

    //inicializo las variables de sumas
    suma_total = 0;   // variable que usara el proceso 0 (raiz)
    suma_parcial = 0; // variable que usaran en todos los procesos para sumar

    // El proceso 0 (raiz) cargo los vectores principales
    if (rank == 0)
    {
        for (int i = 0; i < total; i++)
        {
            vector1[i] = i + 3;
            vector2[i] = i + 2;
        }
    }

    // Divido y envío el vector 1 a los otros procesos siendo padre el resto de procesos recibe los datos con esta funciones
    MPI_Scatter(vector1, elementos, MPI_FLOAT, vector1_local, elementos, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Divido y envío el vector 2 a los otros procesos siendo padre el resto de procesos recibe los datos con esta funciones
    MPI_Scatter(vector2, elementos, MPI_FLOAT, vector2_local, elementos, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // Cada proceso realiza el cálculo de una parte del vector principal
    for (int i = 0; i < elementos; i++)
    {
        suma_parcial = suma_parcial + (vector1_local[i] * vector2_local[i]);
        cout << "Proceso: " << rank
             << " vector1: " << vector1_local[i]
             << " vector2: " << vector2_local[i]
             << " resultado parcial: " << suma_parcial << endl;
    }

    // Cada proceso envia las variables y el proceso raiz recibe las variables de todos los procesos
    MPI_Reduce(&suma_parcial, &suma_total, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso raiz, hago la suma de las variables que se recibieron
    if (rank == 0)
    {
        cout << "Suma Total: " << suma_total << endl;
    }

    // Cada proceso envía su valor al proceso raiz

    // Terminamos la ejecucion de los procesos, despues de esto solo existira
    // la hebra 0
    // ¡Ojo! Esto no significa que los demas procesos no ejecuten el resto
    // de codigo despues de "Finalize", es conveniente asegurarnos con una
    // condicion si vamos a ejecutar mas codigo (Por ejemplo, con "if(rank==0)".
    MPI_Finalize();

    return 0;
}