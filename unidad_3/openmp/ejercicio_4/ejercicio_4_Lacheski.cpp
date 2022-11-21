#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;


#define nthreads 5 // cantidad de hilos que se ejecutaran

int main (){

  int size = nthreads * 5;                        
  int vector1[size];
  int vector2[size];
  int total = 0; 

  srand(time(NULL));
  printf("\nEl vector 1 es: \n");
  for (int i = 0; i < size; i++) {
    //Se carga vector 1 con RANDOM
      vector1[i] = rand() % 100;
      printf("%d - ", vector1[i]);
  }
  printf("\n");
  printf("\nEl vector 2 es: \n");
  for (int i = 0; i < size; i++) {
    //Se carga vector 2 con RANDOM
      vector2[i] = rand() % 100;
      printf("%d - ", vector2[i]);
  }

   printf("\n");

  omp_set_num_threads(nthreads);
  #pragma omp parallel reduction(+:total)  
  {
      int thread = omp_get_thread_num();

      #pragma omp for schedule(static, 5)
      for (int i = 0; i < size ; i++){

        total+= vector1[i] * vector2[i];

        #pragma omp critical
        {
            printf("\n");
            printf("Soy el hilo %d, ",thread);
            printf("El producto en posicion [%d] vectores 1 y 2, (%d x %d), ", i, vector1[i], vector2[i]);
            printf("sumatoria: %d ", total);
            printf("\n");
        }
      }
  }
    //Se informa el resultado total
  printf("\nTotal: %d\n", total);
}  
