#include <omp.h>
#include <iostream>

int main (){

int nthreads;
int thread;
int var = 777 ;

omp_set_num_threads(10);

#pragma omp parallel private(nthreads, thread) firstprivate(var)
  {

  thread = omp_get_thread_num();

  nthreads = omp_get_num_threads();

  std::cout<<"Hola Mundo soy la hebra ="<< thread <<" de "<<nthreads<<" que somos . el val de n es "<< var+thread <<std::endl;

  }

}