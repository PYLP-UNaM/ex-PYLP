#include <omp.h>
#include <iostream>

int main (){

//Éste código se ejecutará solo por el hilo principal o master, hasta llegar a una región paralela

int nthreads;
int thread;
//si definimos nueva_variable dentro de la clausula private cada hilo reiniciará
//su valor a 0 (cero), si queremos mantener el valor asignado fuera de la zona
//paralela entonces debemos definirla con la clausula de compartición firstprivate en ese caso
//se mantendrá su valor asignado es decir 777. 
int nueva_variable = 777;
int suma_total=0;




//PUNTO 2 (HACER QUE EL CÓDIGO DE LA REGIÓN PARALELA SE EJECUTE POR 10 HILOS)
//define la cantidad de hilos ejecutados en las regiones paralelas 

//PUNTO 3
//si eleminamos la clausula private entonces todos los hilos sobreescribiran
//la variable thread, es decir, la variable thread no será mas privada para cada hilo.

//PUNTO 4
//Si creamos una variable fuera de la región paralela y luego la pasamos a la región paralela 
//utilizando la clausula de compartición private, esta variabel será privada para cada hilo
//y por lo tanto se reiniciara su valor para cada hilo a 0 (cero)

//PUNTO 5
//La clausula de compartición firstprivate hace que cada hilo mantenga el valor inicial de la variable creada 
//fuera de la región paralela y cuando se ejecute en la región critica o paralela todos van a mantener el 
//valor, 777 en este caso


omp_set_num_threads(10);

#pragma omp parallel private(nthreads, thread) firstprivate(nueva_variable) reduction(+:suma_total)//primer directiva de openMP
  {

  suma_total=nueva_variable;
  thread = omp_get_thread_num();
  nthreads = omp_get_num_threads();

  //suma_total se reduce, es decir, se suman todos los valores generados en 
  //nueva variable por cada hilo
  suma_total+=thread;


  //hace que cada hilo imprima toda la linea antes de pasar a imprimir los datos del nuevo hilo,
  // para que no se intercale las impresiones 
  #pragma omp critical 
  std::cout<<"Hola Mundo soy la hebra ="<< thread <<" de "<<nthreads<<" que somos el valor de nueva_variables es "<< nueva_variable + thread <<std::endl;

  }

  //se imprimir la variable definida en la clausula de compartición Reduction (suma_total)
  std::cout<<"nueva_variables fuera de la seccion paralela es "<< suma_total <<std::endl;

}