#include <omp.h>
#include <iostream>
#include <sstream>
#include <time.h>

#define NH 10 //Hilos a ejecutar

int main()
{
	using namespace std;

	int thread, suma;
	int totalMultiplos = 0;
	int v[NH];
	// Se utiliza stringstream para concatenar los elementos a imprimir en pantalla
	stringstream stream;
	
	srand(time(NULL));
	cout << "Vector:";
	for (int i = 0; i < NH; i++)
	{
		v[i] = 1+rand()%(100); // v recibe valores aleatorios entre 1 y 100
		cout << " " << v[i];
	}
	cout << endl;

	omp_set_num_threads(NH);

	#pragma omp parallel shared(v) private(stream,thread,suma) reduction(+:totalMultiplos)
	{
		thread = omp_get_thread_num();
		suma = v[(NH+thread-1) % NH] + v[(NH+thread+1) % NH];
		stream << "El hilo ";
		stream << thread;
		stream << " tiene como suma ";
		stream << suma;
		stream << ", que ";
		if (suma % v[thread])
			stream << "no ";
		else
			totalMultiplos += 1;
		stream << "es múltiplo de ";
		stream << v[thread];
		stream << endl;
		cout << stream.str();       
	}
	cout << "Cantidad de múltiplos: " << totalMultiplos << endl;
}
