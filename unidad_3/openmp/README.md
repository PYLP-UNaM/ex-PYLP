# OpenMP

`OpenMP` es una interfaz de programación de aplicaciones para la programación multiproceso de memoria compartida en múltiples plataformas. Permite añadir concurrencia a los programas escritos en C, C++ y Fortran sobre la base del modelo de ejecución fork-join.

La API de `OpenMP` Sigue un modelo escalable con una interfaz simple y flexible para desarrollar aplicaciones paralelas en plataformas que van desde ordenadores personales hasta superordenadores.

La API define únicamente el estándar que hay que seguir para poder utilizar la interfaz.

## Componentes del estandar

---

## Funciones/Directivas

|                                                                                                             |                                                                                                    |                                                                                                         |
| ----------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------- |
| [**pragma omp parallel**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)          | [**pragma omp single**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)   | [**pragma omp taskwait**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)      |
| [**pragma omp for**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)               | [**pragma omp task**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)     | [**pragma omp atomic**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)        |
| [**pragma omp parallel for**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)      | [**pragma omp master**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)   | [**pragma omp flush**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)         |
| [**pragma omp sections**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)          | [**pragma omp critical**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas) | [**pragma omp ordered**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)       |
| [**pragma omp parallel sections**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas) | [**pragma omp barrier**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas)  | [**pragma omp threadprivate**](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_directivas) |

---

## [Clausulas de Compartición de datos](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=omp_clausulas)

|                       |                          |
| --------------------- | ------------------------ |
| default(shared\|none) | lastprivate(list)        |
| shared(list)          | reduction(operator:list) |
| private(list)         | nowait                   |
| firstprivate(list)    |                          |

---

## [Planificadores de bucles](https://lsi.ugr.es/jmantas/ppr/ayuda/omp_ayuda.php?ayuda=schedule)

1. Static
2. Dynamic
3. Guided
4. Auto
5. Runtime

---

## compilando los archivos

para compilar el archivo fuente `.cpp` se debe ejecutar el comando `mpicxx`.

debemos usar la opcion `-fopenmp` para indicarle que es un archivo que usa `OpenMP`

con la opcion `-o` le damos el nombre que queremos al ejecutable.

```sh
mpicxx -fopenmp <archivo_fuente.cpp> -o <archivo_ejecutable>
```

## Ejecutando los archivos

Para ejecutar los programas corremos :

```sh
./<nombre_archivo>
```
