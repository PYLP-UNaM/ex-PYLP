#include <omp.h>
#include <iostream>

#define NH 15

int main (){

    int hilo, totalMultiplos = 0;
    int vectorGlobal[NH] = {13,21,29,16,20,23,56,88,54,65,2,4,7,45,32};

    printf("Vector cargado:\n");
    for (int i = 0 ; i < NH; i++)
    {
        printf(" %d -",vectorGlobal[i]);
    }
    printf("\n\n");

    omp_set_num_threads(NH);
    #pragma omp parallel private(hilo), firstprivate(vectorGlobal) reduction(+:totalMultiplos)
    {
        hilo = omp_get_thread_num();

        int valMedio = vectorGlobal[hilo];
        int valIzq, valDer, suma;

        if(hilo != 0 && hilo != NH-1){
            valIzq = vectorGlobal[hilo-1];
            valDer = vectorGlobal[hilo+1];

        }else{
            if (hilo == 0){
                valIzq = vectorGlobal[NH-1];
                valDer = vectorGlobal[hilo+1];
            }

            if (hilo == NH-1){
                valIzq = vectorGlobal[hilo-1];
                valDer = vectorGlobal[0];
            }
        }

        //suma de valores 
        suma = valIzq + valDer;

        //comprobacion de si es multiplo
        if (suma % valMedio == 0){
            #pragma omp critical
            printf("Soy el hilo %d: calculo %d mod %d  = 0  - Es multiplo \n\n",hilo, suma, valMedio);
            totalMultiplos = 1;
        }else{
            #pragma omp critical
            printf("Soy el hilo %d: calculo %d mod %d != 0  - No es multiplo \n\n",hilo, suma, valMedio);
        }
    }

    printf("Cantidad de múltiplos: %d\n\n",totalMultiplos);

}