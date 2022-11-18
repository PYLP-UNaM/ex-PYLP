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

      // #pragma omp for schedule(static, 2)   
      // Las iteraciones son divididas en partes de tamaño indicado, y las partes se asignan a los hilos mediante RR en el orden del numero de hilo.
      
      // #pragma omp for schedule(dynamic, 2)  
      // Cada hilo ejecuta una parte de las iteraciones, a continuación pide otro parte hasta que no quedan trozos para su distribución.
      
      // #pragma omp for schedule(guided, 2)   
      // Lo mismo que dynamic; pero las partes comienzan siendo grandes y se van reduciendo con forme a lo planificado
      
      #pragma omp for schedule(auto)           // La decisión de la planificación del reparto es delegada en el compilador o el sistema
      for (int i = 0 ; i < N; i++){
          #pragma omp critical
            std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }

  }
}