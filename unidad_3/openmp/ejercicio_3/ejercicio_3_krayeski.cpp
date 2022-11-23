#include <omp.h>
#include <iostream>

#define NH 13

int main (){
    int hilo, totalMultiplos = 0;
    int vectorGlobal[NH] = {10,21,29,40,13,21,29, 20, 12, 28, 33, 11, 5};

    //vector GLOBAL
    for (int i = 0 ; i < NH; i++)
    {
        printf(" %d -",vectorGlobal[i]);
    }
    printf("\n\n");

    omp_set_num_threads(NH);
    #pragma omp parallel private(hilo), firstprivate(vectorGlobal) reduction(+:totalMultiplos)
    {
        hilo = omp_get_thread_num();

        //Obtenemos los valores
        int valorHiloCentro = vectorGlobal[hilo];
        int valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha;

        if(hilo != 0 && hilo != NH-1){
            valorHiloIzquierda = vectorGlobal[hilo-1];
            valorHiloDerecha = vectorGlobal[hilo+1];

        }else{
            if (hilo == 0){
                valorHiloIzquierda = vectorGlobal[NH-1];
                valorHiloDerecha = vectorGlobal[hilo+1];
            }

            if (hilo == NH-1){
                valorHiloIzquierda = vectorGlobal[hilo-1];
                valorHiloDerecha = vectorGlobal[0];
            }
        }

        //Sumamos los extremos
        sumaIzquierdaDerecha = valorHiloIzquierda + valorHiloDerecha;

        //Comprobamos si la suma de los extremos el múltiplo del valor del centro
        if (sumaIzquierdaDerecha % valorHiloCentro == 0){
            #pragma omp critical
            printf("Proceso %d: %d | %d | %d  --  %d + %d = %d  --  %d mod %d  = 0  -- SI es multiplo \n\n",hilo,valorHiloIzquierda, valorHiloCentro, valorHiloDerecha, valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha, sumaIzquierdaDerecha, valorHiloCentro);
            totalMultiplos = 1;
        }else{
            #pragma omp critical
            printf("Proceso %d: %d | %d | %d  --  %d + %d = %d  --  %d mod %d != 0  -- NO es multiplo \n\n",hilo,valorHiloIzquierda, valorHiloCentro, valorHiloDerecha, valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha, sumaIzquierdaDerecha, valorHiloCentro);
        }
    }

    printf("Cantidad de múltiplos: %d\n\n",totalMultiplos); // 4-> La variable tiene la cantidad de multiplos porque usamos la clausula reduction

}