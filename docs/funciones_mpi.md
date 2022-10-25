# Funciones MPI

![alt](../img/operaciones_mpi.gif)

## [Broadcast - MPI_Bcast](https://lsi2.ugr.es/jmantas/ppr/ayuda/mpi_ayuda.php?ayuda=MPI_Bcast)

Envía un mensaje desde un proceso origen a todos los procesos pertenecientes al mismo grupo.

## [Scatter - MPI_Scatter](https://lsi2.ugr.es/jmantas/ppr/ayuda/mpi_ayuda.php?ayuda=MPI_Scatter)

Un proceso raíz trocea un mensaje en partes iguales y los envía individualmente al resto de procesos y a sí mismo.

## [Gather - MPI_Gather](https://lsi2.ugr.es/jmantas/ppr/ayuda/mpi_ayuda.php?ayuda=MPI_Gather)

Recoge una serie de datos de varios procesos en un único proceso raíz (operación en la cual interviene también el propio proceso raíz).

## [Reduce - MPI_Reduce](https://lsi2.ugr.es/jmantas/ppr/ayuda/mpi_ayuda.php?ayuda=MPI_Reduce)

Reduce un valor de un grupo de procesos en un único proceso raíz.
