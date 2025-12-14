#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define PADDING 8

static long num_steps = 100000000;

void serial_code();
void parallel_code();
void parallel_code_no_false_sharing();
void parallel_code_synchronization();
void parallel_code_for_construct();

int main()
{
    // const int MAX_ITER = 10000;

    // float sum = 0;
    // for (float i = 0; i < 1; i+=0.0001) {
    //     sum += 1 / (1 + i*i);
    // }

    // sum *= 4;

    // printf("Pi: %.8f\n", sum);

    serial_code();
    parallel_code();
    parallel_code_no_false_sharing();
    parallel_code_synchronization();
    parallel_code_for_construct();

    return 0;
}

void serial_code()
{
    double step;
    double start = omp_get_wtime(); // trenutak pocetka merenja vremena
    int i;
    double x, pi, sum = 0.0;

    step = 1.0 / (double)num_steps;

    for (i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    double end = omp_get_wtime(); // trenutak zavrsetka merenja vremena

    printf("pi = %lf\n", pi);
    printf("Time elapsed: %lf\n", end - start);
}

void parallel_code()
{
    double step;
    double start = omp_get_wtime();
    double sums[NUM_THREADS];
    double pi = 0.0;
    int nthreads;

    step = 1.0 / (double)num_steps;

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        // printf("id: %d, ", id);

        int nthrds = omp_get_num_threads();
        if (id == 0)
            nthreads = nthrds;

        int i;
        for (i = id, sums[id] = 0; i < num_steps; i += nthrds)
        {
            double x = (i + 0.5) * step;
            sums[id] += 4.0 / (1.0 + x * x);
        }
    }

    for (int i = 0; i < nthreads; i++)
    {
        pi += sums[i];
    }

    pi *= step;
    double end = omp_get_wtime();

    printf("pi = %lf\n", pi);
    printf("Time elapsed paralel: %lf\n", end - start);
}

void parallel_code_no_false_sharing()
{
    double start = omp_get_wtime();

    int nthreads;
    double sum[NUM_THREADS][PADDING];
    double step = 1.0 / (double)num_steps;
    double pi = 0.0;

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
    {
        int i, id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0)
            nthreads = nthrds;
        for (i = id, sum[id][0] = 0; i < num_steps; i += nthrds)
        {
            double x = (i + 0.5) * step;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }

    for (int i = 0; i < nthreads; i++)
    {
        pi += sum[i][0];
    }

    pi *= step;

    double end = omp_get_wtime();

    printf("pi = %lf\n", pi);
    printf("Time elapsed no false sharing: %lf\n", end - start);
}

void parallel_code_synchronization()
{
    double start = omp_get_wtime();
    int nthreads;
    double step = 1.0 / (double)num_steps;
    double pi = 0.0, sum = 0.0;

#pragma omp parallel
    {
        int i, id, nthrds;
        double x, sum = 0.0;

        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id == 0)
            nthreads = nthrds;

        for (i = id; i < num_steps; i += nthrds)
        {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }

#pragma omp critical
        pi += sum;
    }

    pi *= step;

    double end = omp_get_wtime();

    printf("pi = %lf\n", pi);
    printf("Time elapsed synchronization: %lf\n", end - start);
}

void parallel_code_for_construct()
{
    double start = omp_get_wtime();
    double pi = 0.0, sum = 0.0;

    double step = 1.0 / (double)num_steps;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = step * sum;
    double end = omp_get_wtime();

    printf("pi = %lf\n", pi);
    printf("Time elapsed construct: %lf\n", end - start);
}