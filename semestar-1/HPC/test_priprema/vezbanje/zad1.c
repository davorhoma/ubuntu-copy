#include <stdio.h>
#include <omp.h>

void add_arrays(float *a, float *b, float *c, int n)
{
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }
}

double sum_array(double *a, int n)
{
    double sum = 0.0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }

    return sum;
}

void scalar_multiply(float *matrix, int rows, int cols, float alpha)
{
#pragma omp parallel for
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i * cols + j] *= alpha;
        }
    }
}

int min_element(int *a, int n)
{
    int min = a[0];

#pragma omp parallel for reduction(min : min)
    for (int i = 1; i < n; i++)
    {
        if (a[i] < min)
        {
            min = a[i];
        }
    }

    return min;
}

int count_positive(float *a, int n)
{
    int count = 0;

#pragma omp parallel for reduction(+ : count)
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
        {
            count++;
        }
    }

    return count;
}

void compute(float *a, float *b, float *c, int n)
{
    float temp;

#pragma omp parallel for private(temp)
    for (int i = 0; i < n; i++)
    {
        temp = a[i] * b[i];
        c[i] = temp + 1.0f;
    }
}

void work(float *a, float *b, int n)
{

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            for (int i = 0; i < n; i++)
            {
                a[i] = a[i] * 2;
            }

#pragma omp task
            for (int i = 0; i < n; i++)
            {
                b[i] = b[i] + 5;
            }
        }
    }
}

void compute_series(double *a, int n, double start)
{
    double x = start;

    // #pragma omp parallel for firstprivate(x)
    // Ne moze se paralelizovati
    for (int i = 0; i < n; i++)
    {
        x = x + a[i];
        a[i] = x;
    }

    printf("Final x = %f\n", x);
}

void stats(double *a, int n, double *sum, double *sum_sq)
{
    *sum = 0.0;
    *sum_sq = 0.0;

    double temp_sum = 0.0;
    double temp_sum_sq = 0.0;
#pragma omp parallel for reduction(+ : temp_sum, temp_sum_sq)
    for (int i = 0; i < n; i++)
    {
        // *sum += a[i];
        temp_sum += a[i];
        // *sum_sq += a[i] * a[i];
        temp_sum_sq += a[i] * a[i];
    }

    *sum = temp_sum;
    *sum_sq = temp_sum_sq;
}

int find_last_positive(int *a, int n)
{
    int idx = -1;

#pragma omp parallel
    {
        int local_idx = -1;

#pragma omp for
        for (int i = 0; i < n; i++)
            if (a[i] > 0)
                local_idx = i;

#pragma omp critical
        {
            if (local_idx > idx)
                idx = local_idx;
        }
    }

    return idx;
}

void process(int *a, int n)
{
#pragma omp parallel for
    for (int i = 0; i < n; i += 2)
    {
        a[i] = a[i] * 2;
    }
}

void compute_steps(double *a, int n)
{
    int i = 0;
    double x = 1.0;

    // Ne moze se paralelizovati zbog zavisnosti x-sa od prethodne vrednosti
    for (int i = 0; i < n; i++)
    {
        a[i] = x;
        x = x * 0.5;
    }
}

int count_above_threshold(double *a, int n, double threshold)
{
    int count = 0;

#pragma omp parallel for reduction(+ : count)
    for (int i = 0; i < n; i++)
    {
        if (a[i] > threshold)
        {
            count++;
        }
    }

    return count;
}

void f1(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] *= 2;
}

void f2(int *b, int n)
{
    for (int i = 0; i < n; i++)
        b[i] += 5;
}

void work_task(int *a, int *b, int n)
{
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            f1(a, n);
#pragma omp task
            f2(b, n);
        }
    }
}

void scale_and_shift(double *a, int n, double factor) {

    for (int i = 0; i < n; i++)
        a[i] = a[i] * factor + 1.0;
}

void process_blocks(int *a, int n, int block) {
    #pragma omp parallel for
    for (int i = 0; i < n; i += block) {
        {
            #pragma omp task
            for (int j = i; j < i + block && j < n; j++) {
                a[j] *= 2;
            }
        }
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < n; i += block) {
                {
                    #pragma omp task firstprivate(i)
                    for (int j = i; j < i + block && j < n; j++) {
                        a[j] *= 2;
                    }
                }
            }
        }
    }
}

int fib(int n) {
    if (n < 2)
        return n;

    int a, b;
    #pragma omp single
    {
        #pragma omp task
        a = fib(n-1);

        #pragma omp task
        b = fib(n-2);
    }

    #pragma omp taskwait
    return a + b;
}

int sum_chunks(int *a, int n, int chunk) {
    int sum = 0;

    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i += chunk) {
        int local = 0;
        #pragma omp single
        {
            #pragma omp task firstprivate(i)
            for (int j = i; j < i + chunk && j < n; j++)
                local += a[j];
        }

        #pragma omp taskwait
        sum += local;
    }

    return sum;
}


int main(int argc, char *argv[])
{
    double a1[] = {1.0, 2.0, 3.0, 4.0};
    int n1 = 4;

    printf("=== compute_series ===\n");
    compute_series(a1, n1, 0.0);
    printf("a1: ");
    for (int i = 0; i < n1; i++)
        printf("%.2f ", a1[i]);
    printf("\n\n");

    /* ---------- stats ---------- */
    double a2[] = {1.0, 2.0, 3.0, 4.0};
    int n2 = 4;
    double sum, sum_sq;

    printf("=== stats ===\n");
    stats(a2, n2, &sum, &sum_sq);
    printf("sum = %.2f\n", sum);
    printf("sum_sq = %.2f\n\n", sum_sq);

    /* ---------- find_last_positive ---------- */
    int a3[] = {-1, 5, -3, 7, -2};
    int n3 = 5;

    printf("=== find_last_positive ===\n");
    int idx = find_last_positive(a3, n3);
    printf("Last positive index = %d\n\n", idx);

    /* ---------- process ---------- */
    int a4[] = {1, 2, 3, 4, 5, 6};
    int n4 = 6;

    printf("=== process ===\n");
    process(a4, n4);
    printf("a4: ");
    for (int i = 0; i < n4; i++)
        printf("%d ", a4[i]);
    printf("\n\n");

    /* ---------- compute_steps ---------- */
    double a5[5];
    int n5 = 5;

    printf("=== compute_steps ===\n");
    compute_steps(a5, n5);
    printf("a5: ");
    for (int i = 0; i < n5; i++)
        printf("%.5f ", a5[i]);
    printf("\n\n");

    /* ---------- count_above_threshold ---------- */
    double a6[] = {1.5, 3.2, 0.5, 4.8, 2.1};
    int n6 = 5;
    double threshold = 2.0;

    printf("=== count_above_threshold ===\n");
    int count = count_above_threshold(a6, n6, threshold);
    printf("Count > %.2f = %d\n", threshold, count);

    return 0;
}