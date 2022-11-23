#include <omp.h>
#include <iostream>

int main (){

omp_set_num_threads(10); // define la cantidad de hilos a correr

int nhilos;
int hilo;
int NuevoValor = 420;

//Para OpenMP las variables no privadas son compartidas 
//aunque siempre es mas claro indicar las variables compartidas mediante shared 
//#pragma omp parallel private(nhilos, hilo) 
#pragma omp parallel private(nhilos, hilo) firstprivate(NuevoValor)
//Con la clausula private se reserva espacio para almacenar la variable localmente pero no se inicializa 
//si queremos que se inicialice debemos usar fistprivate(NuevoValor)
  {

  hilo = omp_get_thread_num();

  nhilos = omp_get_num_threads(); //obtiene la cantidad de hilos a correr
//Por defecto OpenMP lanzara tantas hebras como núcleos de procesamiento tenga la maquina donde se ejecuta
  std::cout<<"Hola Mundo soy el hilo = "<< hilo <<" de "<<nhilos<<" que somos. "<<"Esta es la variable nueva: "<<NuevoValor<<std::endl;

  }

}