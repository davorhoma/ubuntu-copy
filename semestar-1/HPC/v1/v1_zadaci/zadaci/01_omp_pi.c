#include <stdio.h>
#include <omp.h>

static long num_steps = 100000; // with this settings SERIAL is faster
// static long num_steps = 10000000; // with this settings PARALLEL is faster

double step;
void serial_code();
void parallel_code();

int main() {
    printf("*************** Sekvencijalna implementacija ***************\n");
    serial_code();
    printf("************************************************************\n");

    printf("*************** Paralelna implementacija ***************\n");
    parallel_code();
    printf("************************************************************\n");
}

void serial_code() {
    double start = omp_get_wtime();
    int i;
    double x, pi, sum = 0.0;

    step = 1.0 / (double) num_steps;

    for (i = 0; i < num_steps; i++) { 
        double x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    double end = omp_get_wtime();

    printf("pi = %lf\n", pi);
    printf("Time elapsed: %lf\n", end - start);
}

void parallel_code() {
    double start = omp_get_wtime();
    int i;
    
    step = 1.00 / (double) num_steps;
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
    double end = omp_get_wtime();

    printf("pi = %lf\n", pi);
    printf("Time elapsed: %lf\n", end - start);
}