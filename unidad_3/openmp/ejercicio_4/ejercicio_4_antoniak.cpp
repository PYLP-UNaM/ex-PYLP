#include <omp.h>
#include <iostream>
#include <sstream>
#include <time.h>

#define NH 3 //Hilos a ejecutar
#define CINCO 5

int main()
{
	using namespace std;

	const int espacio = NH*CINCO;
	int producto, i;
	int totalCritical = 0;
	int totalAtomic = 0;
	int totalReduction = 0;
	int vectorUno[NH*CINCO];
	int vectorDos[NH*CINCO];
	// Se utiliza stringstream para concatenar los elementos a imprimir en pantalla
	stringstream stream;

	srand(time(NULL));
	cout << "Vector uno:";
	for (i = 0; i < espacio; i++)
	{
		vectorUno[i] = 1+rand()%(100); // v recibe valores aleatorios entre 1 y 100
		cout << " " << vectorUno[i];
	}
	cout << endl;
	cout << "Vector dos:";
	for (i = 0; i < espacio; i++)
	{
		vectorDos[i] = 1+rand()%(100); // v recibe valores aleatorios entre 1 y 100
		cout << " " << vectorDos[i];
	}
	cout << endl;

	omp_set_num_threads(NH);

	#pragma omp parallel shared(vectorUno,vectorDos,totalCritical,totalAtomic) private(stream,producto,i) reduction(+:totalReduction)
	{
		#pragma omp for schedule(static, CINCO)
		for (i = 0; i < espacio; i++)
		{
			producto = vectorUno[i] * vectorDos[i];
			#pragma omp critical
				totalCritical += producto;
			#pragma omp atomic
				totalAtomic += producto;
			totalReduction += producto;
			stream << "El hilo ";
			stream << omp_get_thread_num();
			stream << " realizó producto entre vectores en el lugar ";
			stream << i;
			stream << ", cuyo resultado fue ";
			stream << producto;
			stream << "\n";
		}
		cout << stream.str();
	}
	if ((totalReduction == totalCritical) && (totalReduction == totalAtomic))
		cout << "Producto escalar: " << totalReduction << endl;
}
