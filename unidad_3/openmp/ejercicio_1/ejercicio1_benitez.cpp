#include <omp.h>
#include <iostream>

int main (){

int nthreads;
int thread;
int nueva_variable = 777;

// Establecemos la cantidad de hilos a ejecutar
omp_set_num_threads(10);

#pragma omp parallel private(nthreads, thread) firstprivate(nueva_variable)
  {
  // Si eliminamos la cláusula 'private' las variables globales podrán ser accedidas por todos los hilos

  // Por otro lado, si utilizamos 'private', las variables son independientes a cada hilo, 
  // pero pierden el valor declarado anteriormente; para mantenerlo se usa "firstprivate"

  thread = omp_get_thread_num();
  nthreads = omp_get_num_threads();

  #pragma omp critical
    printf("Hola Mundo soy la hebra = %d de %d que somos. Esta es la variable nueva =  %d \n", thread, nthreads, nueva_variable+thread);
  }

}