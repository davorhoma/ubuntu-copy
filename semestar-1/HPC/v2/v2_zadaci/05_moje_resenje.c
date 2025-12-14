#include <omp.h>
#include <stdio.h>
#include <unistd.h>

#ifndef N
#define N 45
#endif

int fib(int n) {
    if (n == 0 || n == 1)
        return n;

    if (n < 20) {
        return fib(n - 1) + fib(n - 2);
    }

    int a, b;

#pragma omp task shared(a)
    a = fib(n - 1);

#pragma omp task shared(b)
    b = fib(n - 2);

#pragma omp taskwait
    return a + b;
}

int main() {
    int res;

    double end, start = omp_get_wtime();

#pragma omp parallel
#pragma omp single
    res = fib(N);

    end = omp_get_wtime();
    printf("fib(%d): %d. Vreme izvršenja: %lf.\n", N, res, end - start);
}