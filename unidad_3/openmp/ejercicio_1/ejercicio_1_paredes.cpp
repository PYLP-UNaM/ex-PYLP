#include <omp.h>
#include <iostream>
#include <sstream>

int main ()
{
	using namespace std;
	int nthreads;
	int thread;
	// Se utiliza stringstream para concatenar los elementos a imprimir en pantalla
	stringstream stream;
	int nuevaVariable = 777;

	// Se establece la cantidad de hilos a ejecutar, como pide el punto 2
	omp_set_num_threads(10);

	/*
	   Si se elimina la cláusula 'private', las variables nthreads y thread
	   tendrán lugares únicos en memoria para cada uno; donde estos últimos
	   se comparten entre todos los hilos, por lo que el orden de ejecución
	   de instrucciones entre los hilos puede modificar la ejecución
	   apropiada del algoritmo y daría posibilidad a un comportamiento
	   inesperado. Esto explica lo solicitado en el punto 3.
	*/
	#pragma omp parallel private(nthreads, thread, stream) firstprivate(nuevaVariable)
	{
		thread = omp_get_thread_num();
		nthreads = omp_get_num_threads();

		/*
		   Si se utiliza private (y no firstprivate), el valor de las
		   variables será iniciado con el correspondiente por defecto
		   del tipo; esto es 0 para la variable nuevaVariable (por
		   ser de tipo int). Por eso se comporta así para el punto 4.
		*/
		nuevaVariable += thread;
		stream << "Hola Mundo soy la hebra = ";
		stream << thread << " de " << nthreads;
		stream << " que somos. ";
		stream << "El valor de la variable nueva aquí es ";
		stream << nuevaVariable << endl;
		// Enviar un elemento a la salida es una operación atómica
		// Enviar varios elementos son varias operaciones (deja de ser atómico)
		cout << stream.str();
	}
}