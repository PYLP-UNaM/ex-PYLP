#include <omp.h>
#include <iostream>

//definir cantidad de hilos
#define threads 10

int main()
{

  int nthreads;
  int thread;
  int var = 777;

  //ejecutar por 10 Hilos
  omp_set_num_threads(threads);

#pragma omp parallel private(nthreads, thread) firstprivate(var)
  {
    thread = omp_get_thread_num();

    var = var + thread;
    nthreads = omp_get_num_threads();

    std::cout << "Hola Mundo soy la hebra = " << thread << " de " << nthreads << " que somos. tengo la variable :" << var << std::endl;
  }
}