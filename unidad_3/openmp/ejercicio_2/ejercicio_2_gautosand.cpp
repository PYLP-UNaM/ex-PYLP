#include <omp.h>
#include <iostream>

#define N 20
#define nthreads 4

int main (){

  int thread;

  omp_set_num_threads(nthreads);

  #pragma omp parallel private(thread)
  {
      thread = omp_get_thread_num();
      #pragma omp for schedule(dynamic, 2) // el dynamic divide los datos de forma aleatoria para cada hilo
      //#pragma omp for schedule(static, 2)// el static divide la cantidad de datos segun el argumento pasado ordenado por los hilos
      //#pragma omp for schedule(guided, 2)
      /*se configura las iteraciones por bloque, parecido a dynamic pero el decide el tamanio de bloque inicial
      y lo va reduciendo hasta el tamanio minimo*/
      //#pragma omp for schedule(auto)// el sistema o el compilador se encargan de la division                        
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
          std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }

  }
}