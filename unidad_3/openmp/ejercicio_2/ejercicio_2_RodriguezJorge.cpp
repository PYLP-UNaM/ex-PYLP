#include <omp.h>
#include <iostream>
#define N 10
#define nthreads 4

int main (){
  int thread;
  omp_set_num_threads(nthreads);

    #pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();

        /*  Punto 2 - La directiva #pragma omp for antes de una sentencia for controla la ejecución del 
            for entre todos los hilos (todos realizan una vez el for e imprime una vez del 0 al 9).  
            Si se omite esta directiva, cada hilo haria un for imprimiendo del 0 al 9 */

        // Punto 3.1 - Las iteraciones son divididas en partes de tamaño pasado como parámetro 
        // #pragma omp for schedule(static, 2)   

        // Punto 3.2 - Cada hilo ejecuta una parte de las iteraciones (divide de manera aleatoria)
        // #pragma omp for schedule(dynamic, 2)  

        // Punto 3.3 - Igualq que dynamic; pero Las partes comienzan siendo grandes y se van reduciendo
        // #pragma omp for schedule(guided, 2)   

        // Punto 3.4 - El compilador o el sistema se encarga de la decisión de la plantificación del reparto
        #pragma omp for schedule(auto)           
            for (int i = 0 ; i < N; i++){
                std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
            }
    }
}