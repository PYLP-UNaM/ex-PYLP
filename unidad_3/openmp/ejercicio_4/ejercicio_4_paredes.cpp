/*
1. Usando una Variable compartida `total`, cargando a la vez que se realiza la carga en `producto`.
- Resuelve el problema con `#pragma omp critical` a la hora de escribir la variable compartida.
- Resuelve el problema con `#pragma omp atomic` a la hora de escribir la variable compartida.
2. Usando una clausula de comparticion `reduction`
*/

#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define N 5
#define nthreads 4

int main (){
  srand(time(NULL));
  int thread;
  int vectorSize = N * nthreads;

  int vector1[vectorSize];
  int vector2[vectorSize];
  int total = 0;
  int product;

  // CARGAR VECTORES DE FORMA ALEATORIA
  for (int i = 0; i < vectorSize; i++) {
      vector1[i] = rand() % 100;
      vector2[i] = rand() % 100;
  }

  // IMPRIMIR VECTOR 1
  cout << endl;
  cout << "VECTOR 1: " << endl;
  for (int i = 0; i < vectorSize; i++) {
      cout << vector1[i] << " - ";
  }
  cout << endl;

  // IMPRIMIR VECTOR 2
  cout << endl;
  cout << "VECTOR 2: " << endl;
  for (int i = 0; i < vectorSize; i++) {
      cout << vector2[i] << " - ";
  }
  cout << endl;

  omp_set_num_threads(nthreads);
  #pragma omp parallel reduction(+:total)
  for (int i = 0 ; i < vectorSize; i++){
    thread = omp_get_thread_num();
    product = vector1[i] * vector2[i];
    total+= product;
    #pragma omp critical
    {
        printf("\n");
        printf("Soy el hilo %d, ",thread);
        printf("multipleque los valores de la posicion %d de los vectores, (%d x %d), ", i, vector1[i], vector2[i]);
        printf("de momento el semi total es: %d ", total);
        printf("\n");
    }
  }
  cout << "Total: " << total << endl;
}