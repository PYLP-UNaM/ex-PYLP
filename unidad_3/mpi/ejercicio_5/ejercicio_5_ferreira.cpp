
#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main (int argc, char *argv[])
{
    int sizeVec, size, rank;

    MPI_Init(&argc,&argv); // Inicializa el entorno MPI
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Número de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identificador del proceso

  // Creación y carga del vector global
    sizeVec = size * 5; // Se asigna 5 porque es lo que se pide para este ejercicio.
    vector<int> vectorGlobal, vectorLocal;
    vectorGlobal.resize(sizeVec, 0); // resize para modificar el tamaño del vector al valor especificado.
    vectorLocal.resize(sizeVec/size, 0); 
    if (rank == 0) { 
        cout << " Vector global " << endl;
        for (int i = 0; i < sizeVec; ++i) {
            vectorGlobal[i] = i + 1; // vectorGlobal 1, 2, 3, ..., sizeVec  
            cout << vectorGlobal[i] << " - ";         
            } 
        cout << endl; 
    }

    // Distribución de los valores del vector global al local
    MPI_Scatter(&vectorGlobal[0], // Valores a compartir
            sizeVec / size, // Cantidad de datos a enviar a cada proceso
            MPI_INT, // Tipo de dato que se enviará
            &vectorLocal[0], // Variable donde se recibe los datos
            sizeVec / size, // Cantidad de datos que se recibe en cada proceso
            MPI_INT, // Tipo de dato que se recibirá
            0,  // Proceso principal que reparte los datos
            MPI_COMM_WORLD); // Comunicador global

    // Impresion de los subvectores locales
    cout << " Vector recibido en el proceso " << rank << endl;
    for (int i = 0; i < sizeVec / size; i++){
        cout << vectorLocal[i] << " - ";
    }
    cout << endl;

    //Cálculo si el valor en la posición i es múltiplo del rango + 2.
    //dicho valor se reemplaza por V=1 F=0
    for (int i = 0; i < sizeVec / size; i++) {
        if (vectorLocal[i] % (rank + 2) == 0)
            vectorLocal[i] = 1;
        else
            vectorLocal[i] = 0;
    } 

    MPI_Gather(&vectorLocal[0], // Valores a compartir
               sizeVec / size, // Cantidad de datos a enviar a cada proceso
               MPI_INT, // Tipo de dato que se enviará
               &vectorGlobal[0], // Variable donde se recibe los datos
	           sizeVec / size, // Cantidad de datos que se recibe en cada proceso
               MPI_INT, // Tipo de dato que se recibirá
               0, // Proceso principal que recibe los datos
	           MPI_COMM_WORLD); // Comunicador global

    if (rank == 0){
        cout << " Vector global unificado " << endl;
        for(int i = 0; i < sizeVec; ++i) {
            cout << vectorGlobal[i] << " - ";
        }
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}