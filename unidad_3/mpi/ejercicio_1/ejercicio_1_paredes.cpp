/* hacer un programa que imprima por pantalla el saludo "Hola Mundo soy el proceso _`X`_, de _`Y`_ que somos" donde:

   > - X sera el identificador del proceso (rango)
   > - Y el número de procesos que fueron lanzados de forma paralela. */

    #include <stdio.h>
    #include <mpi.h>

    int main(int argc, char *argv[])
    {
        int rank, size;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        printf("Hola Mundo soy el proceso %d, de %d que somos\n", rank, size);

        MPI_Finalize();

        return 0;
    }