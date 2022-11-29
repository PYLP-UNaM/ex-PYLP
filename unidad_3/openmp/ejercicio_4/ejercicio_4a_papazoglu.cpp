#include <omp.h>
#include <iostream>
#define NH 3

//Prototipo de funciones
void cargaVectores(int v1[], int v2[],int n);
void imprimirVectores(int v1[],int v2[],int n);


int main (){

    int hilo, nthreads;
    int suma_total=0;
    int size_vector=NH*5;
    /*int vector1[size_vector];
    int vector2[size_vector];*/

    //Solo a modo de prueba inicializamos los dos vectores con valores fijos
    //con esto sabemos que el resultado escalar de estos 2 vectores es = 1240
    int vector1[]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int vector2[]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    //cargaVectores(vector1,vector2,size_vector);
    imprimirVectores(vector1,vector2,size_vector);
      

    //define la cantidad de hilos ejecutados en las regiones paralelas 
    omp_set_num_threads(NH);

      #pragma omp parallel private(hilo, nthreads) 
      {
        hilo = omp_get_thread_num();        
        nthreads = omp_get_num_threads();
        int sum=0;

        #pragma omp for schedule(static,5)
              for(int i=0; i < size_vector;i++)
              {
                sum = sum + vector1[i] * vector2[i];    
              }
              //es necesario esta directiva para que no se intercale la siguiente instrucción
              #pragma omp atomic
              suma_total += sum;
        }

      //se imprimir la variable compartida suma_total
      std::cout<<"El resultado escalar entre los dos vectores usando una variable compartida es: "<< suma_total <<std::endl;

}

void cargaVectores(int v1[], int v2[],int n){
  srand(time(NULL));
  
  for (int i = 0; i < n; ++i) {
      v1[i] = rand() % 100;//1+rand()%((50+1)-1); // Vector A recibe valores aleatorios entre 1 y 50
      v2[i] = rand() % 100;//1+rand()%((100+50)-1); // Vector B recibe valores aleatorios entre 50 y 100
  }
  printf("\n\n");
}

void imprimirVectores(int v1[],int v2[],int n){
  //Imprimimos los elementos de los vectores 
  printf("Vector 1\n");
  for (int i = 0; i < n; i++)
  {
    printf(" %i-",v1[i]);
  }
  printf("\n");
  printf("Vector 2\n");
  for (int i = 0; i < n; i++)
  {
    printf(" %i-",v2[i]);
  }
  printf("\n");



}