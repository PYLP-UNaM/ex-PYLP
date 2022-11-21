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
      // Dynamic scheduling
      // #pragma omp for schedule(dynamic, 2) 
      // Dynamic divide los datos de forma aleatoria para cada hilo
      // ---- //

      // Static scheduling
      // #pragma omp for schedule(static, 2) 
      // Static divide la cantidad de datos segun el argumento pasado ordenado por los hilos
      // ---- //

      // Guided scheduling
      // #pragma omp for schedule(guided, 2)
      /*  Guided configura las iteraciones por bloque, parecido a dynamic pero el decide el tamaño 
          de bloque inicial y lo va reduciendo hasta el tamanio minimo  */
      // ---- //

      // Auto scheduling
      #pragma omp for schedule(auto) 
      // El sistema o el compilador se encargan de la division    
      // ---- //

      for (int i = 0 ; i < N; i++){
        #pragma omp critical
          std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }
  }
}
