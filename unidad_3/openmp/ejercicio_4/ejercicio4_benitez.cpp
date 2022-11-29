#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;

// Cantidades de hilos
#define nthreads 4

int main (){

    int size = nthreads * 5;                        
    int vectorUno[size];
    int vectorDos[size];
    int total = 0; 

    srand(time(NULL));
  
    // Se cargan los vectores de forma random
    printf("\nEl primer vector es: \n");
    for (int i = 0; i < size; i++) {
        vectorUno[i] = rand() % 100;
        printf("%d / ", vectorUno[i]);
    }
  
    printf("\nEl segundo vector es: \n");
    for (int i = 0; i < size; i++) {
        vectorDos[i] = rand() % 100;
        printf("%d / ", vectorDos[i]);
    }

    omp_set_num_threads(nthreads);
    #pragma omp parallel reduction(+:total)  
    {
        int thread = omp_get_thread_num();

        #pragma omp for schedule(static, 5)

        for (int i = 0; i < size ; i++){
            total+= vectorUno[i] * vectorDos[i];
            #pragma omp critical
            {
                printf("\n");
                printf("Soy el hilo %d, ",thread);
                printf("multipleque los valores de la posicion %d de los vectores, (%d x %d), ", i, vectorUno[i], vectorDos[i]);
                printf("de momento el semi total es: %d ", total);
                printf("\n");
            }
        }
    }
    
    // Se informa el resultado total
    printf("\nEl total es de: %d\n", total);
}  