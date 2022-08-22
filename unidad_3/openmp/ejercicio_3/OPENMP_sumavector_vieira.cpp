//SUMA LOS ELEMENTOS DE UN VECTOR

#include <stdio.h>
#include <omp.h>
#include <iostream>

#define longi 100
#define canthilos 4

int main()
{

	omp_set_num_threads(canthilos); //Se setea el numero de hilos en 4
	int vec1[longi];				// Vector de longitud 100
	int hilo, sum, salto, begin, end, total;

////////////////////////////////////////////////////////
//////// 1- CARGA DEL VECTOR  DE FORMA PARALELA ////////
///////////////////////////////////////////////////////
#pragma omp parallel private(hilo) // Inicia la seccion paralela y define a 'hilo' como privado
	{
		hilo = omp_get_thread_num(); // carga en 'hilo' el hilo que ejecuta esta seccion

#pragma omp for schedule(static, 25) // se define un for paralelo. La asignacion de los hilos esta definida por el SCHEDULE pudiendo ser schedule( [static|dynamic|guided|auto] )
		for (int i = 0; i < longi; i++)
		{
			vec1[i] = hilo * i; // vec en la posicion i es la posicion por el hilo que tomo esa posicion
		}
	}

	////////////////////////////////////////////////////
	// 2- SE IMPRIME EL VECTOR DE MANERA SECUENCIAL ///
	//////////////////////////////////////////////////
	printf("VECTOR 1:");
	printf("\n");
	for (int i = 0; i < longi; i++)
	{
		printf("%d - ", vec1[i]);
	}
	printf("\n");

	//////////////////////////////////////////////////////////
	// 3- SUMA DE TODOS LOS ELEMENTOS DEL VECTOR - PARALELO //
	/////////////////////////////////////////////////////////
	/** cada hilo calcula la suma parcial de una parte del vector
	 * 	hilo 0 de la posicion 0 a 24
	 *  hilo 1 de la posicion 25 a 49
	 * 	hilo 2 de la posicion 50 a 74
	 *  hilo 3 de la posicion 75 a 99 
	 * */
	sum = 0;
	total = 0;
#pragma omp parallel private(hilo, begin, end) firstprivate(sum) shared(total) // 'hilo' 'begin' y 'end' es privado a cada hilo                          \
																			   // 'sum' en cada hilo empieza en 0 en él se va sumando la parte del hilo \
																			   // 'total' variable compartida por todos los hilos para calcular la suma total del vector
	{
		hilo = omp_get_thread_num();		   // obtengo el nro del hilo
		salto = longi / omp_get_num_threads(); // cantidad de posiciones por hilo. 100/4 = 25
		begin = hilo * salto;				   // donde empieza cada hilo: hilo_0 0*25= 0, hilo_1 1*25= 25, hilo_2 2*25= 50, hilo_3 3*25= 75
		end = begin + salto;				   // hasta donde va cada hilo hilo_0 0+25= 25, hilo_1 25+25=50, hilo_2 50+25=75, hilo_3 75+25=100

#pragma omp parallel for shared(total)
		for (int i = begin; i < end; i++)
		{
			sum += vec1[i];
			total += vec1[i];
		}
		printf("la suma del hilo %d es: %d - la suma parcial es: %d \n", hilo, sum, total);
	}
	printf("la suma TOTAL = %d \n", total);
}
//	Las instrucciones propias de OPENMP utilizadas son:
//	- omp_set_num_threads
//	- omp_get_thread_num
//	- omp_get_num_threads
