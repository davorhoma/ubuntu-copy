#include <omp.h>
#include <stdio.h>
#include <unistd.h>

#ifndef N
#define N 38
#endif

int fib(int n) {
    if (n == 0 || n == 1)
        return n;

    int a, b;

    if (n > 10) {
        #pragma omp task shared(a)
        a = fib(n-1);
    
        #pragma omp task shared(b)
        b = fib(n-2);
    
        #pragma omp taskwait
    } else {
        a = fib(n-1);
        b = fib(n-2);
    }

    return a + b;
}

int main()
{
    int res;

    double end, start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        res = fib(N);

        #pragma omp barrier
    }
    end = omp_get_wtime();
    printf("fib(%d): %d. Vreme izvršenja: %lf.\n", N, res, end - start);
}