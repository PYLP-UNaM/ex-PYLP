#include <omp.h>
#include <iostream>

int main (){

int nthreads;
int thread;
int varprivate = 777 ;
int varfirstprivate = 777 ;
omp_set_num_threads(2);
#pragma omp parallel private(nthreads, thread,varprivate) firstprivate(varfirstprivate)
  {
//varprivate = 555;
  thread = omp_get_thread_num();

  nthreads = omp_get_num_threads();

std::cout<<"Hola Mundo soy la hebra ="<< thread <<" de "<<nthreads<<" que somos" <<std::endl;
std::cout<<"varprivate"<< varprivate <<" varprivate"   << varfirstprivate  <<std::endl;
/*La diferencia entre private y firstprivate es que firstprivate mantiene el valor afuera de la 
seccion paralela mientras que private no inicializa el valor*/
  }

}