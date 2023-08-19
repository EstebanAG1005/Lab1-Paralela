#include <stdio.h>

double compute_pi_seq(long long n)
{
    double factor = 1.0;
    double sum = 0.0;
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
    printf("Estimación de PI: %lf\n", compute_pi_seq(n));
    return 0;
}
