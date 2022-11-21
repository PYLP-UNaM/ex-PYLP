/*
## TAREAS
1. Definir una variable de alcance global `totalMultiplos`
2. Definir a nivel de bloque `#omp paralell` la clausula de comparticion `reduction(+:totalMultiplos)`
3. Si la suma de los vecinos es multiplo del elemento en la posicion `hilo` setear la variable `totalMultiplos` en 1
4. fuera de la region paralela imprimir la variable `totalMultiplos` que valor tiene? ¿Por qué?
*/

#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

#define N 10
#define nthreads 4

int main (){
  srand(time(NULL));
  int thread;
  int vector[nthreads];
  int limiteVector = nthreads - 1;
  int totalMultiplos = 0;

  // Carga aleatoria del vector e impresion de sus elementos
  cout << endl;
  cout << "VECTOR: " << endl;
  for (int i = 0; i < nthreads; i++) {
      vector[i] = rand() % 100;
      cout << vector[i] << " - ";
  }
  cout << endl;

  omp_set_num_threads(nthreads);
  #pragma omp parallel private(thread) firstprivate(limiteVector, vector) reduction(+:totalMultiplos)
  {
      int previous, next, sumVecinos,isMultiplo;
      thread = omp_get_thread_num();

      if (thread == 0) {
        previous = limiteVector;
        next = thread + 1;
      }
      else if (thread == limiteVector) {
        previous = thread - 1;
        next = 0;
      }
      else {
        previous = thread - 1;
        next = thread + 1;
      }

      sumVecinos = vector[previous] + vector[next];
      isMultiplo = sumVecinos % vector[thread] == 0 ? true : false;
      #pragma omp critial
      {
        cout << endl;
        cout << "Soy el hilo " << thread << endl;
        cout << sumVecinos << " % " << vector[thread] << " = " << sumVecinos % vector[thread] << endl;
        cout << endl;
      }

      if (isMultiplo) totalMultiplos = 1;

  }

  cout << "La cantidad de multiplos es " << totalMultiplos << endl;
}
