#include <omp.h>
#include <iostream>

int main (){

int nthreads;
int thread;

//Lanzamos x cantidad de hilos
omp_set_num_threads(7);

int nuevaVariable = 777;

#pragma omp parallel private(nthreads, thread) firstprivate(nuevaVariable)
  {
    thread = omp_get_thread_num();
    nuevaVariable= nuevaVariable + thread;

    nthreads = omp_get_num_threads();

    printf("Hola mundo soy el hilo %d de %d que somos. Nueva variable vale: %d \n",thread, nthreads, nuevaVariable);

  }

  printf("Valor de la nueva variable fuera de la seccion paralela: %d \n", nuevaVariable);

}