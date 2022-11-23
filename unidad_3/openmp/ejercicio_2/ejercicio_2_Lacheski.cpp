#include <omp.h>
#include <iostream>

#define N 10
#define nthreads 4

int main()
{
    int thread;
    omp_set_num_threads(nthreads);
    printf("\n");
    printf("STATIC \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(static)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
        }
    }
    printf("\n");
    printf("DYNAMIC \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(dynamic)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
        }
    }
    printf("\n");
    printf("GUIDED \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(guided)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
        }
    }
    printf("\n");
    printf("AUTO \n");
#pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
#pragma omp for schedule(auto)
        for (int i = 0; i < N; i++)
        {
            printf("Soy %d ejecuto la iteracion %d \n", thread, i);
        }
    }
}
