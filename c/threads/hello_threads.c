#include <omp.h>
#include <stdio.h>
#include <math.h>

int main(void) {
    int i;

    #pragma omp parallel num_threads(omp_get_num_procs()) 
    {
        #pragma omp for 
            for (i = 0; i < 1000; i++) {
                printf("Hello from thread %d, iteration %d\n", omp_get_thread_num(), i);
            }
    }
}