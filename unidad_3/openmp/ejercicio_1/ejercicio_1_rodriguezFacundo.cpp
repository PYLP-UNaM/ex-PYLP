#include <omp.h>
#include <iostream>

int main(){

    int nthreads;
    int thread;

    omp_set_num_threads(10); // Punto 2.

    int numero = 777; // Punto 4. Si se define dentro del #pragma omp parallel pasa a ser compartida

    // Punto 3. Si se omite la clausula private, 'numero' pasa a ser una variable compartida  

    #pragma omp parallel private(nthreads, thread) firstprivate(numero) // Punto 5.
    {
        
      thread = omp_get_thread_num();

      nthreads = omp_get_num_threads();
        
      std::cout<<"Hola Mundo soy la hebra = "<< thread <<" de "<<nthreads<<" que somos"<<std::endl;
            
    }
}
