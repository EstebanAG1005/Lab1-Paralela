// piSeriesScheduling.c
#include <stdio.h>
#include <omp.h>

int main()
{
    int n = 10000000; // 10e6
    double sum = 0.0;
    int thread_count = 4; // Asumiendo que tienes 4 cores. Ajustar según necesidad.
    int block_size;
    char *sched_type[] = {"static", "dynamic", "guided", "auto"};

    for (int i = 0; i < 4; i++)
    {
        printf("Scheduling type: %s\n", sched_type[i]);
        if (i < 3)
        { // auto no acepta block size
            int block_sizes[] = {16, 64, 128};
            for (int j = 0; j < 3; j++)
            {
                block_size = block_sizes[j];
                printf("Block size: %d\n", block_size);
                omp_set_schedule(i, block_size);
#pragma omp parallel for num_threads(thread_count) reduction(+ : sum) schedule(runtime)
                for (int k = 0; k < n; k++)
                {
                    double factor = (k % 2 == 0) ? 1.0 : -1.0;
                    sum += factor / (2 * k + 1);
                }
                printf("Approximated value of PI: %lf\n\n", 4.0 * sum);
            }
        }
        else
        {
#pragma omp parallel for num_threads(thread_count) reduction(+ : sum) schedule(runtime)
            for (int k = 0; k < n; k++)
            {
                double factor = (k % 2 == 0) ? 1.0 : -1.0;
                sum += factor / (2 * k + 1);
            }
            printf("Approximated value of PI: %lf\n\n", 4.0 * sum);
        }
    }
    return 0;
}
