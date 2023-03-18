#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// prototype
double serial_integral(int a, int b, int N, double (*f)(double));
double parallel_integral(int a, int b, int N, double (*f)(double));
double PI_serial_ingration_via_epsilon();
double PI_parallel_ingration_via_epsilon();
double pi(double x);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <N>\n", argv[0]);
        exit(1);
    }

    int N = atoi(argv[1]);

    double start, end;
    double result;
    int a = 0;
    int b = 1;

    // serial
    printf("Serial implementation\n");
    start = omp_get_wtime();
    result = serial_integral(a, b, N, pi);
    end = omp_get_wtime();
    printf("Result: %f Time: %f\n", result, end - start);

    // parallel
    printf("Parallel implementation\n");
    start = omp_get_wtime();
    result = parallel_integral(a, b, N, pi);
    end = omp_get_wtime();
    printf("Result: %f Time: %f\n", result, end - start);

    // serial via epsilon
    printf("Serial implementation via epsilon\n");
    start = omp_get_wtime();
    result = PI_serial_ingration_via_epsilon();
    end = omp_get_wtime();
    printf("Result: %f Time: %f\n", result, end - start);

    // parallel via epsilon
    printf("Parallel implementation via epsilon\n");
    start = omp_get_wtime();
    result = PI_parallel_ingration_via_epsilon();
    end = omp_get_wtime();
    printf("Result: %f Time: %f\n", result, end - start);

    printf("\n\nMATH_PI: %f\n", M_PI);

    printf("Done\n");

    return 0;
}

// Serial implementation
double serial_integral(int a, int b, int N, double (*f)(double))
{
    double sum = 0;
    double dx = (double) (b - a) / (double) N;

    for (int i = 0; i < N; i++)
    {
        double x = a + i * dx;
        sum += f(x)*dx;
    }

    return sum;
}

// Parallel implementation
double 
parallel_integral(int a, int b, int N, double (*f)(double))
{
    double sum = 0;
    double dx = (double) (b - a) / (double) N;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++)
    {
        double x = a + i * dx;
        sum += f(x)*dx;
    }

    return sum;
}

double pi(double x)
{
    return 4.0 / (1.0 + x*x);
}

// smallest number x that satisfies 1 + x*x != 1
double epsilon()
{
    double x = 1.0;
    while (1 + x*x != 1)
    {
        x /= 2;
    }
    return x * 2;
}

double PI_serial_ingration_via_epsilon()
{
    double sum = 0;
    double dx = epsilon();

    for (double x = 0; x < 1; x += dx)
    {
        sum += pi(x)*dx;
    }

    return sum;
}

double PI_parallel_ingration_via_epsilon()
{
    double sum = 0;
    const double dx = epsilon();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < (int) ceil(1/dx); i++)
    {
        double x = i * dx;
        sum += pi(x)*dx;
    }
    return sum;
}