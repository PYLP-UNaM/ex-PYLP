#include "mpi.h"
#include <iostream>
using namespace std;

#define RAIZ 0
#define PORCION 5
int main (int argc, char*argv[])
{
	MPI_Init(&argc, &argv); //inicialización de MPI
	int rank, size;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); //id de proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size);//cantidad de procesos en el comunicador global
	int vectorSize = size * PORCION;
	int vector[vectorSize], result[vectorSize];
	int buzon[PORCION]; //buzón para recibir los elementos
	if (rank == RAIZ){
		//carga vectores aleatoreamente 
		for (int i = 0; i < vectorSize; i++) {
			vector[i]= rand() % 100;
		}
		//impresión del vector
		cout << endl;
		cout << "VECTOR: " << endl;
		for (int i = 0; i < vectorSize; i++) {
			cout << vector[i] << " - ";
		}
		cout << endl;
	}
	MPI_Scatter(
		&vector, //lo que se distribuirá entre los procesos
		PORCION, //nro de elementos que se envía a cada proceso
		MPI_INT, //tipo de dato de lo que se va a enviar
		&buzon, //en dónde cada proces hace la recepción
		PORCION, //nro de elementos a recibir
		MPI_INT, //tipo de datos de lo que se va a recibir
		RAIZ, //quién realiza el envío
		MPI_COMM_WORLD //los procesos que participan en la distribución
	);
	cout << endl;
	cout << "Buzón de " << rank << endl;
	for (int i = 0; i < PORCION; i++) {
		cout << buzon[i] << " - ";
	}
	cout << endl;
	int resultadoParcial[PORCION];
	for (int i = 0; i < PORCION; i++) {
		resultadoParcial[i] = buzon[i] % (rank + 2) == 0 ? 1 : 0;
	}
	cout << endl;
	MPI_Gather(
		&resultadoParcial, //qué se va a enviar
		PORCION,  //cantidad de elementos a enviar
		MPI_INT,  //tipo de dato de lo qe se enviará
		&result,  //dónde se reciben los elementos
		PORCION, //cantidad de elementos a recibir
		MPI_INT, //tipo de datos de lo que se va a recibir
		RAIZ, //quién va a recibir
		MPI_COMM_WORLD  //entre quiénes se hace la reunión de datos		
	);
	if (rank == RAIZ) {
		cout << endl;
		cout << endl;
		cout << endl;
		//impresión del vector
		cout << "RESULTADO: " << endl;
		for (int i = 0; i < vectorSize; i++) {
			cout << result[i] << " - ";
		}
		cout << endl;
		cout << endl;
	}
	

 MPI_Finalize();
 return 0;
}