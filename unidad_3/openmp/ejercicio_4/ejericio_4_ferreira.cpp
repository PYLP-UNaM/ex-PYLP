#include <omp.h>
#include <iostream>

#define NH 4
#define CINCO 5 

int main (){
    int hilo, producto, total=0, lng=NH*CINCO;
    int vectorGlobal1[lng], vectorGlobal2[lng];
    for (int i = 0; i < lng; i++){
        vectorGlobal1[i] = i;
        vectorGlobal2[i] = (lng-1) - i;
    }
    omp_set_num_threads(NH);
    #pragma omp parallel private(hilo, producto), firstprivate(vectorGlobal1, vectorGlobal2, lng) reduction(+:total)
    {
        hilo = omp_get_thread_num();
        producto = 0;
        #pragma omp for schedule(auto) 
        for (int i=0; i<lng; i++){
            #pragma omp atomic
            producto+=vectorGlobal1[i]*vectorGlobal2[i];
        }
        #pragma omp atomic
        total+=producto;
        printf("Resultado parcial del proceso %d es: %d \n", hilo, total);
    }
    printf("\nProducto escalar: %d\n\n",total);
}