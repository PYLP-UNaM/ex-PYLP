#include "mpi.h"
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int tamanio, rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 2) {
        if (rank == 0) {
            cout << "No se especificó nro de elementos, multiplo de la cantidad de entrada, por defecto sera " << size * 100;
            cout << "\nUso: <ejecutable> <cantidad>" << endl;
        }
        tamanio = size * 100;
    } else {
        tamanio = atoi(argv[1]);
        if (tamanio < size) tamanio = size;
        else {
            int i = 1, num = size;
            while (tamanio > num) {
                ++i;
                num = size*i;
            }
            if (tamanio != num) {
                if (rank == 0)
                    cout << "Cantidad cambiada a " << num << endl;
                tamanio = num;
            }
        }
    }

    // Se crean y rellenan los vectores
    vector<long> VectorA, VectorB, VectorALocal, VectorBLocal;
    VectorA.resize(tamanio, 0);
    VectorB.resize(tamanio, 0);
    VectorALocal.resize(tamanio/size, 0);
    VectorBLocal.resize(tamanio/size, 0);
    if (rank == 0) {
        for (long i = 0; i < tamanio; ++i) {
            VectorA[i] = i + 1; // Vector A recibe valores 1, 2, 3, ..., tamanio
            VectorB[i] = (i + 1)*10; // Vector B recibe valores 10, 20, 30, ..., tamanio*10
        }
    }

    // se reparten los valores del vector A
    MPI_Scatter(&VectorA[0], // Valores a compartir
            tamanio / size, // Cantidad que se envia a cada proceso
            MPI_LONG, // Tipo del dato que se enviara
            &VectorALocal[0], // Variable donde recibir los datos
            tamanio / size, // Cantidad que recibe cada proceso
            MPI_LONG, // Tipo del dato que se recibira
            0,  // proceso principal que reparte los datos
            MPI_COMM_WORLD); // Comunicador (En este caso, el global)
    //Se reparten los valores del vector B
    MPI_Scatter(&VectorB[0],tamanio / size,MPI_LONG,&VectorBLocal[0],tamanio / size,MPI_LONG,0,MPI_COMM_WORLD);

    // se calcula la multiplicacion escalar entre vectores
    long producto = 0;
    for (long i = 0; i < tamanio / size; ++i) {
        producto += VectorALocal[i] * VectorBLocal[i];
    }
    long total;

    //Se reunen los datos en un solo proceso, aplicando la operación aritmética: suma
    MPI_Reduce(&producto, // Elemento a enviar
            &total, // Variable donde se almacena la reunion de los datos
            1, // Cantidad de datos a reunir
            MPI_LONG, // Tipo del dato que se reunira
            MPI_SUM, // Operacion aritmetica a aplicar
            0, // Proceso que recibira los datos
            MPI_COMM_WORLD); // Comunicador

    if (rank == 0)
        cout << "Total = " << total << endl;

    MPI_Finalize();
    return 0;
}