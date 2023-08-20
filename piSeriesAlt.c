#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 4

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Threads> <Cantidad de N>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    long num_terms = atol(argv[2]);

    if (num_threads <= 0 || num_terms <= 0) {
        printf("Invalid input parameters.\n");
        return 1;
    }

    double sum = 0.0;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        long thread_id = omp_get_thread_num();
        long start = thread_id * (num_terms / num_threads);
        long end = (thread_id + 1) * (num_terms / num_threads);
        double local_sum = 0.0;

        for (long i = start; i < end; ++i) {
            double term = (i % 2 == 0) ? 1.0 / (2 * i + 1) : -1.0 / (2 * i + 1);
            local_sum += term;
        }

        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    end_time = omp_get_wtime();

    double pi = 4.0 * sum;
    printf("Estimación de PI: %f\n", pi);
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);

    return 0;
}
