#include <omp.h>
#include <iostream>
#include <sstream>

// Se cambió N por NUM para distinguir de NTHREADS
#define NUM 10
// Se cambio nthreads a todo mayúscula por ser constante
#define NTHREADS 4

int main ()
{
	using namespace std;
	int thread;
	stringstream stream;
	omp_set_num_threads(NTHREADS);

	#pragma omp parallel private(thread, stream)
	{
		/*
		   Cuando no se utiliza la directiva
		   #pragma omp for, todos los hilos
		   ejecutarán el mismo código;
		   imprimiendo el texto NUM veces,
		   multiplicado por la cantidad
		   de núcleos del procesador.
		*/
		thread = omp_get_thread_num();
		
		/*
		   Al utilizar #pragma omp for, se
		   distribuye la ejecución del
		   bucle entre los hilos; según
		   esté ajustado por el planificador,
		   el cual es auto por defecto.
		   En pocas palabras, el bucle se
		   ejecuta una sola vez; no como
		   antes, que se realiza cierta
		   cantidad de veces (núcleos del
		   procesador).
		*/
		
		// 3.1
		#pragma omp for schedule(static)
		for (int i = 0 ; i < NUM; i++)
		{
			stream << "Soy el proceso static ";
			stream << thread;
			stream << " ejecutando la iteración ";
			stream << i << "\n";
		}
		cout << stream.str();
		stream.str("");
		
		// 3.2
		#pragma omp for schedule(dynamic, 1)
		for (int i = 0 ; i < NUM; i++)
		{
			stream << "Soy el proceso dynamic ";
			stream << thread;
			stream << " ejecutando la iteración ";
			stream << i << "\n";
		}
		cout << stream.str();
		stream.str("");
		
		// 3.3
		#pragma omp for schedule(guided, NUM)
		for (int i = 0 ; i < NUM; i++)
		{
			stream << "Soy el proceso guided ";
			stream << thread;
			stream << " ejecutando la iteración ";
			stream << i << "\n";
		}
		cout << stream.str();
		stream.str("");
		
		// 3.4
		#pragma omp for schedule(auto)
		for (int i = 0 ; i < NUM; i++)
		{
			stream << "Soy el proceso auto ";
			stream << thread;
			stream << " ejecutando la iteración ";
			stream << i << "\n";
		}
		cout << stream.str();
	}
}
