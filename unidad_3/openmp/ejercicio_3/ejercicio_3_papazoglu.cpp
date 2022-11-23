#include <omp.h>
#include <iostream>


#define NH 8

int main (){

  int hilo, totalMultiplos = 0;
  int vectorGlobal[NH]={5,10,15,13,25,30,10,40};

  //Imprimimos los elementos del vector 
  printf("Vector global\n");
  for (int i = 0; i < NH; i++)
  {
    printf(" %i-",vectorGlobal[i]);
  }
  printf("\n");

  //seteamos la cantidad de hilos
  omp_set_num_threads(NH);

  
  //Iniciamos la sección paralela
  #pragma omp parallel private(hilo), firstprivate(vectorGlobal) reduction(+:totalMultiplos) 
  {
    //Guardamos en hilo la cantidad de hilos lanzados
    hilo = omp_get_thread_num();

    int valorHiloCentro = vectorGlobal[hilo];
    int valorHiloIzquierda, valorHiloDerecha, sumaIzquierdaDerecha;

    if(hilo!=0 && hilo!=NH-1)//es un elemeto del vector que tiene ambos vecinos adyascentes
    {
      valorHiloIzquierda=vectorGlobal[hilo-1];
      valorHiloDerecha=vectorGlobal[hilo+1];
    }else //es un elemento del vector que esta en uno de los extremos del vector 
    {
      if(hilo==0)//es el primer elemento del vector tiene vecino derecho adyascente y el izquierdo es el último elemento
      {
        valorHiloIzquierda=vectorGlobal[NH-1];
        valorHiloDerecha=vectorGlobal[hilo+1];
      }
      if(hilo==NH-1)//es el último elemento del vector tiene vecino izquierdo adyascente y el derecho es el primer elemento
      {
        valorHiloIzquierda=vectorGlobal[hilo-1];
        valorHiloDerecha=vectorGlobal[0];
      }
    }

    //Sumamos los vecinos
    sumaIzquierdaDerecha=valorHiloIzquierda+valorHiloDerecha;

    //Preguntamos si la suma es múltiplo del valor del vector en la posición del hilo
    if(sumaIzquierdaDerecha % valorHiloCentro == 0)
    {
      #pragma omp critical 
      printf("Proceso %d: %d | %d | %d -- %d + %d = %d -- %d mod %d = 0 -- Multiplo \n\n", hilo,valorHiloIzquierda,valorHiloCentro,valorHiloDerecha,valorHiloIzquierda,valorHiloDerecha,sumaIzquierdaDerecha,sumaIzquierdaDerecha,valorHiloCentro);
      totalMultiplos=1;
    }else
    {
      #pragma omp critical 
      printf("Proceso %d: %d | %d | %d -- %d + %d = %d -- %d mod %d <> 0 -- NO Multiplo \n\n", hilo,valorHiloIzquierda,valorHiloCentro,valorHiloDerecha,valorHiloIzquierda,valorHiloDerecha,sumaIzquierdaDerecha,sumaIzquierdaDerecha,valorHiloCentro);
    }
  }
  //Imprimirmos la variable de la clausula de comparticion reduction (suma la cantidad de múltiplos)
  printf("cantidad de multipos: %i\n\n",totalMultiplos);
}