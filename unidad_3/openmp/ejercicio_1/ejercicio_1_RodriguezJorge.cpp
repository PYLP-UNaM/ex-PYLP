#include <omp.h>
#include <iostream>

/* Punto 1 - Por defecto, se ejecutan el mismo número de hilos que la cantidad de núcleos del procesador
   (en mi caso, son 4) */

// Número de hilos
#define THREAD_NUM 10

int main (){
int nthreads;
int thread;

/* Punto 4 - En caso que se defina la variable dentro del #pragma omp parallel pasa a ser compartida, 
   pero utlizando la cláusula "private", cada hilo realizará una copia de la variable dentro de su ejecución
   tomando el valor que se le asigne dentro de un hilo */
int var = 777;

// Punto 2 - Ejecución por 10 hilos
omp_set_num_threads(THREAD_NUM);

/* Punto 3 - Si se omite la clausula private, las variables puede ser modificadas por cualquier 
   hilo (pasarán a ser compartidas) */

/* Punto 5 - Con firstprivate todo el código dentro del "omp parallel" tendrá la variable privada, 
   inicializada con el valor 777 */

#pragma omp parallel private(nthreads, thread)
  {
    thread = omp_get_thread_num();
    nthreads = omp_get_num_threads();
    std::cout<<"Soy el hilo "<< thread <<" de un total de "<< nthreads << std::endl;
  }
}