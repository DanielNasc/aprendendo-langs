#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// macros (testing)
#define HEAD(imp_type) \
    printf("Implementation: %s\n", imp_type); \
    start = omp_get_wtime();
#define PRINT_RESULT_AND_TIME(result, start, end) \
    end = omp_get_wtime(); \
    printf("Result: %f Time: %f\n", result, end - start); \
    printf("Absolute error: %f\n", fabs(result - M_PI)); \
    printf("Relative error: %f\n", fabs(result - M_PI) / M_PI); \
    printf("\n");
#define IMPS_W_ARGS(imp_type, f, a, b, N, g) \
    HEAD(imp_type) \
    result = f(a, b, N, g); \
    PRINT_RESULT_AND_TIME(result, start, end)
#define IMPS_WO_ARGS(imp_type, f) \
    HEAD(imp_type) \
    result = f(); \
    PRINT_RESULT_AND_TIME(result, start, end)

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

    char *binary = NULL;

    // serial
    IMPS_W_ARGS("Serial", serial_integral, a, b, N, pi);

    // parallel
    IMPS_W_ARGS("Parallel", parallel_integral, a, b, N, pi);

    // serial via epsilon
    IMPS_WO_ARGS("Serial implementation via epsilon", PI_serial_ingration_via_epsilon);

    // parallel via epsilon
    IMPS_WO_ARGS("Parallel implementation via epsilon", PI_parallel_ingration_via_epsilon);

    printf("\nMATH_PI: %f\n", M_PI);

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