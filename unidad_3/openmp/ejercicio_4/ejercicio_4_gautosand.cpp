#include <omp.h>
#include <iostream>

#define NH 6
#define CINCO 5 

int main (){
    int hilo, producto, total=0, lng=NH*CINCO;
    int vector1[lng], vector2[lng];

    for (int i = 0; i < lng; i++){
        vector1[i] = i+1;
        vector2[i] = i*i;

    }

    printf("Vector 1 cargado:\n");
    for (int i = 0 ; i < lng; i++)
    {
        printf(" %d -",vector1[i]);
    }
    printf("\n\n");

    printf("Vector 2 cargado:\n");
    for (int i = 0 ; i < lng; i++)
    {
        printf(" %d -",vector2[i]);
    }
    printf("\n\n");

    omp_set_num_threads(NH);

    #pragma omp parallel private(hilo, producto), firstprivate(vector1, vector2, lng) reduction(+:total)
    {
        hilo = omp_get_thread_num();
        producto = 0;

        #pragma omp for schedule(auto) 
        for (int i=0; i<lng; i++){
            #pragma omp atomic
            producto+=vector1[i]*vector2[i];
        }

        #pragma omp atomic
        total+=producto;
        
        printf("Resultado local del hilo %d es de: %d \n", hilo, total);

    }

    printf("\nResultado final producto escalar: %d\n\n",total);

}