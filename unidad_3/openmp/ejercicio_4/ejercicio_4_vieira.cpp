#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define N 5
#define nthreads 4

int main()
{
    srand(time(NULL));
    int thread;
    int vectorSize = N * nthreads;

    int vector1[vectorSize];
    int vector2[vectorSize];
    int total = 0;
    int product;

    // CARGAR VECTORES DE FORMA ALEATORIA
    for (int i = 0; i < vectorSize; i++)
    {
        vector1[i] = rand() % 100;
        vector2[i] = rand() % 100;
    }

    // IMPRIMIR VECTOR 1
    cout << endl;
    cout << "VECTOR 1: " << endl;
    for (int i = 0; i < vectorSize; i++)
    {
        cout << vector1[i] << " - ";
    }
    cout << endl;

    // IMPRIMIR VECTOR 2
    cout << endl;
    cout << "VECTOR 2: " << endl;
    for (int i = 0; i < vectorSize; i++)
    {
        cout << vector2[i] << " - ";
    }
    cout << endl;

    omp_set_num_threads(nthreads);
#pragma omp parallel for private(thread, product) reduction(+ \
                                                            : total)
    for (int i = 0; i < vectorSize; i++)
    {
        thread = omp_get_thread_num();
        product = vector1[i] * vector2[i];
        total += product;
#pragma omp critical
        cout << "Hilo " << thread << " - Indice " << i << "   " << vector1[i] << " X " << vector2[i] << " = " << product << endl;
    }

    cout << "Total: " << total << endl;
}
