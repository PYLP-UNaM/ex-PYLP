#include <omp.h>
#include <iostream>

#define NH 6
#define CINCO 5 

int main (){
    int hilo, producto, total=0, lng=NH*CINCO;
    int vectorA[lng], vectorB[lng];
    
    // Carga de Vectores
    for (int i = 0; i < lng; i++){
        // El vector A se carga del 0+1, hasta 6*5 (30)
        vectorA[i] = i+1;
        // El vector B es el doble del vector B
        vectorB[i] = vectorA[i]*2;
    }

    printf("Vector A:\n");
    for (int i = 0 ; i < lng; i++)
    {
        printf("[%d]",vectorA[i]);
    }
    printf("\n");

    printf("Vector B:\n");
    for (int i = 0 ; i < lng; i++)
    {
        printf("[%d]",vectorB[i]);
    }
    printf("\n\nResultados por hilos\n");

    omp_set_num_threads(NH);

    #pragma omp parallel private(hilo, producto), firstprivate(vectorA, vectorB, lng) reduction(+:total)
    {
        hilo = omp_get_thread_num();
        producto = 0;

        #pragma omp for schedule(auto) 
        for (int i=0; i<lng; i++){
            //#pragma omp critical
            #pragma omp atomic
                producto+=vectorA[i]*vectorB[i];
        }

        //#pragma omp critical
        #pragma omp atomic
            total+=producto;
            printf("Hilo %d: %d \n", hilo, total);

    }

    printf("\nProducto escalar: %d\n",total);

}

/* Ejecución hilo 0
   - 1*2 = 2
   - 2*4 = 8
   - 3*6 = 18
   - 4*8 = 32
   - 5*10 = 50
   Producto Escalar = 2+8+18+32+50 = 110
*/ 