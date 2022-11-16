#include <omp.h>
#include <iostream>

#define N 15
#define nthreads 3

int main (){

  int thread;

  omp_set_num_threads(nthreads);

  #pragma omp parallel private(thread)
  {
      thread = omp_get_thread_num();

      /*
      si agregamos la directiva #pragma omp for antes del bucle
      lo que sucede es que se divide la cantidad de iteraciones
      por la cantidad de hilos, cada hilo ejecuta un número de iteraciones
      
      #pragma omp for
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
        std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }*/


      /*
      Podemos agregar a la directiva #pragma omp la clausula schedule y sus planificadores
      como parametros, los planificadores son static, dynamic, guided y auto 
      */

      //dynamic
      //los hilos ejecutan 5 iteraciones cada uno pero cualquiera lo hace
      //por ej en éste caso 4 hilos y 10 iteraciones siempre ejecutan 5 iteraciones cada
      //hilo pero pueden ser cualquiera de los hilos 
      /*#pragma omp for schedule(dynamic,5) 
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
        std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }*/


      //static
      //Los hilos ejecutan 5 iteraciones cada uno pero lo hacen en forma secuencial
      //por ej en éste caso 4 hilos y 10 iteraciones siempre ejecutan 5 iteraciones cada
      //hilo pero siempre son el hilo 0 y el 1
      /*#pragma omp for schedule(static,5) 
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
        std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }*/


      //auto
      //En éste caso todos los hilos ejecutan iteraciones pero es el compilador 
      //o el runtime el que determina en forma automática cuantas iteraciones realizará
      //cada hilo
      /*#pragma omp for schedule(auto) 
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
        std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }*/


      //guided
      //guided: threadpool de pedazos de tamaño decreciente. El tamaño de los bloques 
      //van decreciendo en cada iteración 
      //según:number_of_iterations_rclearemaining / number_of_threads.
      //El tamaño del pedazo indica el tamaño mínimo. 
      //El valor por defecto del pedazo es 1.
      #pragma omp for schedule(guided,2)
      for (int i = 0 ; i < N; i++){
        #pragma omp critical
        std::cout<<"Soy el proceso "<<thread<<" ejecuto al iteracion "<<i<<std::endl;
      }
  }
}