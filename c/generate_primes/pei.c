#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int checkPrime(int n);
double genPrime(int n, int iterations, int *isPrimeResults);

typedef struct primeVec {
    int *primes;
    int size;
} PrimeVec;

int m2(int n) {
    PrimeVec *primes = malloc(sizeof(PrimeVec));
    primes->primes = malloc(sizeof(int));
    primes->size = 0;

    int i = 0;
    while(primes->size < n) {
        i++;
        if (checkPrime(i)) {
            primes->size++;
            primes->primes = realloc(primes->primes, primes->size * sizeof(int));
            primes->primes[primes->size - 1] = i;
        }
    }

    printf("ITERATIONS: %d\n", i);

    return primes->primes[primes->size - 1];
}

int main(int argc, char *argv[]) {
    int N;

    if (argc < 2) {
        printf("Enter a number: ");
        scanf("%d", &N);
    } else {
        N = atoi(argv[1]);
    }

    double s = omp_get_wtime();
    printf("The %dth prime is %d\n", N, m2(N));
    double e = omp_get_wtime();

    printf("Time taken to compute %d iterations of CheckPrime: %f seconds\n", N, e - s);

    return 0;

    int iterations = pow(2, N);
    int *isPrimeResults = malloc(iterations * sizeof(int));

    double start = omp_get_wtime();
    #pragma omp parallel for shared(isPrimeResults)
    for (int i = 0; i <= iterations; i++) {
        isPrimeResults[i] = checkPrime(i + 1);
    }
    double end = omp_get_wtime();



    printf("Time taken to compute %d iterations of CheckPrime: %f seconds\n", iterations, end - start);

    // for (int i = 0; i < iterations; i++) {
    //     printf("isPrimeResults[%d]: %d\n", i, isPrimeResults[i]);
    // }

    start = omp_get_wtime();
    double result = genPrime(N, iterations, isPrimeResults);
    end = omp_get_wtime();

    printf("Time taken to compute %d iterations of genPrime: %f seconds\n", iterations, end - start);    

    printf("the %dth prime is %f\n", N, result);

    return 0;
}

int checkPrime(int n) {
    if (n == 2 || n == 3) return 1;
    else if (n < 2 || n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i <= sqrt(n); i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}

double genPrime(int n, int iterations, int *isPrimeResults) {
    double result = 1.0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 1; i <= iterations; i++) {
        int den = 1.0;

        for (int j = 1; j <= i; j++) {
            den += isPrimeResults[j - 1];
        }

        if (den == 0) continue;

        double sum = pow((double) n / den, 1.0 / (double) n);

        // printf("sum: int %d double %f\n", floor(sum), sum);

        result += floor(sum);
        // printf("result: %f\n", result);
    }

    return result;
}