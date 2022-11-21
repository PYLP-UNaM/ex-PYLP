#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;

// Cantidades de hilos
#define nthreads 40 

int main (){

    int vector[nthreads];
    int totalMultiplos = 0;

    srand(time(NULL));

    // Se carga el vector con numeros aleatorios
    printf("\nEl vector es: \n");
    for (int i = 0; i < nthreads; i++) {
        vector[i] = rand() % 100;
        printf("%d / ", vector[i]);
    }

    omp_set_num_threads(nthreads);

    #pragma omp parallel firstprivate(vector) reduction(+:totalMultiplos)  
    {
        int izquierda;
        int derecha;
        int thread;

        thread = omp_get_thread_num();

        // Se realiza la operacion correspondiente dependiendo la posición del vector (inicio, final o medio)
        if (thread == 0) { 
            izquierda = 0;
            derecha = vector[thread + 1];
        } else if (thread == nthreads - 1) {
            izquierda = vector[thread - 1];
            derecha = 0;
        } else {
            izquierda = vector[thread - 1];
            derecha = vector[thread + 1];
        }        

        // Se verifica si la sumatoria del valor a su izquierda + el valor a la derecha, es múltiplo del valor en su posición
        if ((izquierda + derecha) % vector[thread] == 0) {
            totalMultiplos = 1;
        }
    }
    
    //Se informa el resultado total
    printf("\nEl total de multiplos es de: %d\n", totalMultiplos);
}