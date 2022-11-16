#include <omp.h>
#include <iostream>

#define NH 15

int main (){

    int hilo, totalMultiplos = 0;
    int vector[NH] = {13,21,29,16,20,23,56,88,54,65,2,4,7,45,32};

    printf("Valores del vector:");
    for (int i = 0 ; i < NH; i++)
    {
        printf("[%d]",vector[i]);
    }
    printf("\n");

    omp_set_num_threads(NH);
    
    #pragma omp parallel private(hilo), firstprivate(vector) reduction(+:totalMultiplos)
    {
        hilo = omp_get_thread_num();
        int medio = vector[hilo];
        int izquierda, derecha, suma;

        if(hilo != 0 && hilo != NH-1){
            izquierda = vector[hilo-1];
            derecha = vector[hilo+1];
        }else{
            if (hilo == 0){
                izquierda = vector[NH-1];
                derecha = vector[hilo+1];
            }

            if (hilo == NH-1){
                izquierda = vector[hilo-1];
                derecha = vector[0];
            }
        }

        // Sumando los valores 
        suma = izquierda + derecha;

        // Es multiplo?
        if (suma % medio == 0){
            #pragma omp critical
                printf("Hilo %d: %d mod %d  = 0 (es múltiplo)\n",hilo, suma, medio);
                totalMultiplos = 1;
        } else {
            #pragma omp critical
                printf("Hilo %d: %d mod %d != 0 (no es múltiplo)\n",hilo, suma, medio);
        }
    }

    printf("Cantidad de múltiplos: %d\n\n",totalMultiplos);

}