#include <omp.h>
#include <iostream>
using namespace std;

#define NH 10 //Hilos a ejecutar

int main(){
    int totalMultiplos = 0;
    int v[NH] = {14,62,25,5,10,45,4,12,20,5};

    omp_set_num_threads(NH);
    
    #pragma omp parallel firstprivate(v) reduction(+:totalMultiplos)
    {
        int thread, suma;
        thread = omp_get_thread_num();

        //Fuera de los extremos
        if(thread != 0 && thread != NH-1){
            suma = v[thread-1] + v[thread+1];
        //en los extremos
        }else{ 
            if(thread == 0)
                suma = v[NH-1] + v[thread+1];
            if(thread == NH-1)
                suma = v[thread-1] + v[0];
        }
        //Comprobar si es multiplo o no
        if (suma % v[thread] == 0){
            #pragma omp critical
            printf("Soy el hilo %d: El número %d Es multiplo de %d porque mod = 0\n",thread, suma, v[thread]);
            totalMultiplos = 1;
        }else{
            #pragma omp critical
            printf("Soy el hilo %d: El número %d No es multiplo de %d porque mod != 0\n",thread, suma, v[thread]);
        }        
    }
    printf("Cant. Múltiplos: %d\n",totalMultiplos);
}