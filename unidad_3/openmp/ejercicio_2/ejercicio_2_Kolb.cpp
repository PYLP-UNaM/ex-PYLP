#include <omp.h>
#include <iostream>

#define N 10
#define nhilos 4

int main (){

  int hilo;

  omp_set_num_threads(nhilos);

  #pragma omp parallel private(hilo)
  {
      hilo = omp_get_thread_num();

        //#pragma omp for schedule(static, 5) //El planif. static recibe por parámetro el nro de iteraciones que reparte a cada hilo, reparte hasta que se queda sin iteraciones
		//#pragma omp for schedule(dynamic, 5)//El planif. dinamic recibe por parámetro el nro de iteraciones x bloque. Cuando un hilo se queda sin trabajo pide un nuevo bloque, así hasta que no hay mas iteraciones
        //#pragma omp for schedule( guided, 1) //recibe por parámetro el nro mín de iter. x bloque. Actúa por demanda como el planif. dinamic pero él decide el tamaño de bloque inicial, y lo va reduciendo hasta el tamaño mín. pasado x parametro
        #pragma omp for schedule(auto)//La planificación se deja en manos del sistema

        //Con la directiva #pragma omp for podemos indicar que las iteraciones de un bucle for 
        //han de ser repartidas entre los distintos hilos.	
        //el planificador "shedule" permite controlar la reparticion de iteraciones paralelas
            for (int i = 0; i < N; i++)
			{
				#pragma omp critical //
				std::cout << "Soy el proceso " << hilo << " ejecuto la iteración " << i << std::endl;
			}

  }
}


