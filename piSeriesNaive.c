#include <stdio.h>
#include <omp.h>

double compute_pi_naive(long long n, int thread_count)
{
    double factor = 1.0;
    double sum = 0.0;
#pragma omp parallel for num_threads(thread_count) reduction(+ : sum)
    for (long long k = 0; k < n; k++)
    {
        sum += factor / (2 * k + 1);
        factor = -factor;
    }
    return 4.0 * sum;
}

int main()
{
    long long n = 1000000; // Un millón como ejemplo
    int thread_count = 4;  // 4 threads como ejemplo
    printf("Estimación de PI: %lf\n", compute_pi_naive(n, thread_count));
    return 0;
}
