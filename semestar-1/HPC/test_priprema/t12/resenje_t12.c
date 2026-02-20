#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N ((int)1e6)
#define INC 14
#define DEC 7
#define MAX_FIB 987
#define NUM_ITERS 100

typedef struct Data {
    int value;
    int fib_value;
} Data;

int fib(int n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }

int do_stuff(Data *arr, int i) {
    int sum = 0;
    for (int k = 0; k < NUM_ITERS; k++) {
        sum += fib(arr[i].value);
    }
    return sum % MAX_FIB + 1;
}

void init_array(Data **arr) {

    *arr = (Data *)malloc(N * sizeof(Data));
    if (NULL == *arr)
        exit(1);

    for (size_t i = 0; i < N; i++) {
        int rndm = rand() % 15 + 2;
        (*arr)[i].value = rndm;
        (*arr)[i].fib_value = rndm;
    }
}

int get_i(int x) {
    // You do not want to know
    int i = x % 2 ? x * 3 - 4 : x * 2 - 3;
    if (i < 0)
        i = 0;
    if (i >= N)
        i = N - 1;
    return i;
}

int sequential_processing(Data *arr) {
    Data *local = (Data *)malloc(N * sizeof(Data));
    int *hist = (int *)calloc(MAX_FIB + 1, sizeof(int));
    int x, y, i = 0, max_freq = 0;

    if (NULL == local)
        exit(1);

    for (y = 0; y < N; y++)
        local[y] = arr[y];

    double end, start = omp_get_wtime();
    x = 0;
    while (x < N) {
        i = get_i(x);
        y = do_stuff(local, i);
        local[i].fib_value = y;

        x += INC;
        x -= DEC;
    }

    for (i = 0; i < N; i++) {
        hist[local[i].fib_value]++;
    }

    for (i = 0; i < MAX_FIB + 1; i++) {
        if (hist[i] > max_freq) {
            max_freq = hist[i];
        }
    }
    end = omp_get_wtime();

    free(hist);
    free(local);

    printf("[SEQUENTIAL] Time spent: %.5f\n", end - start);

    return max_freq;
}

int parallel_processing_1(Data *arr) {
    Data *local = (Data *)malloc(N * sizeof(Data));
    int *hist = (int *)calloc(MAX_FIB + 1, sizeof(int));
    int x, y, i = 0, max_freq = 0;

    if (NULL == local)
        exit(1);

    for (y = 0; y < N; y++)
        local[y] = arr[y];

    double end, start = omp_get_wtime();
#pragma omp parallel private(y, i)
    {
#pragma omp for
        for (x = 0; x < N; x += (INC - DEC)) {
            i = get_i(x);
            y = do_stuff(local, i);

            local[i].fib_value = y;
        }

#pragma omp single
        for (i = 0; i < N; i++) {
            hist[local[i].fib_value]++;
        }

#pragma omp for reduction(max : max_freq)
        for (i = 0; i < MAX_FIB + 1; i++) {
            if (hist[i] > max_freq) {
                max_freq = hist[i];
            }
        }
    }

    end = omp_get_wtime();

    free(hist);
    free(local);

    printf("[PARALLEL 1] Time spent: %.5f\n", end - start);

    return max_freq;
}

int parallel_processing_2(Data *arr) {
    Data *local = (Data *)malloc(N * sizeof(Data));
    int *hist = (int *)calloc(MAX_FIB + 1, sizeof(int));
    int x, y, i = 0, max_freq = 0;

    if (NULL == local)
        exit(1);

    for (y = 0; y < N; y++)
        local[y] = arr[y];

    double end, start = omp_get_wtime();
    x = 0;

#pragma omp parallel private(y, i) firstprivate(x)
    {
#pragma omp single
        {
            while (x < N) {
#pragma omp task
                {
                    i = get_i(x);
                    y = do_stuff(local, i);
                    local[i].fib_value = y;
                }

                x += INC;
                x -= DEC;
            }
        }

#pragma omp single
        for (i = 0; i < N; i++) {
            hist[local[i].fib_value]++;
        }

#pragma omp for reduction(max : max_freq)
        for (i = 0; i < MAX_FIB + 1; i++) {
            if (hist[i] > max_freq) {
                max_freq = hist[i];
            }
        }
    }

    end = omp_get_wtime();

    free(hist);
    free(local);

    printf("[PARALLEL 2] Time spent: %.5f\n", end - start);

    return max_freq;
}

int main(int argc, char *argv[]) {
    time_t rand_time_seed = time(0);
    srand(rand_time_seed);

    Data *arr;
    init_array(&arr);
    int seq_max = sequential_processing(arr);
    printf("[SEQUENTIAL] Maximum frequency: %d\n", seq_max);
    int par_max = parallel_processing_1(arr);
    printf("[PARALLEL 1] Maximum frequency: %d\n", par_max);
    int par_max_task = parallel_processing_2(arr);
    printf("[PARALLEL 2] Maximum frequency: %d\n", par_max_task);

    if (seq_max != par_max || seq_max != par_max_task) {
        printf("Inconsistent results.\n");
    }

    free(arr);
    return 0;
}
