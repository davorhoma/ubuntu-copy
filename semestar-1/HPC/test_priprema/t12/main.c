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

// Helper functions ignore these
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

        x += INC;
        x -= DEC;

        local[i].fib_value = y;
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

int parallel_processing(Data *arr) {
    Data *local = (Data *)malloc(N * sizeof(Data));
    int *hist = (int *)calloc(MAX_FIB + 1, sizeof(int));
    int x, y, i = 0, max_freq = 0;

    if (NULL == local)
        exit(1);

    for (y = 0; y < N; y++)
        local[y] = arr[y];

    double end, start = omp_get_wtime();

    // TODO: make it faster
    #pragma omp parallel private(i, y)
    {
        #pragma omp for
        for (int x = 0; x < N; x += INC - DEC)
        {
            // while (x < N) {
                i = get_i(x);
                y = do_stuff(local, i);
                local[i].fib_value = y;
        
                // x += INC;
                // x -= DEC;
            // }
        }
    
        // int nthreads = omp_get_num_threads();
        // int thread_num = omp_get_thread_num();
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

    printf("[PARALLEL] Time spent: %.5f\n", end - start);

    return max_freq;
}

int main(int argc, char *argv[]) {
    time_t rand_time_seed = time(0);
    srand(rand_time_seed);

    Data *arr;
    init_array(&arr);
    int seq_max = sequential_processing(arr);
    printf("[SEQUENTIAL] Maximum frequency: %d\n", seq_max);
    int par_max = parallel_processing(arr);
    printf("[PARALLEL] Maximum frequency: %d\n", par_max);

    if (seq_max != par_max) {
        printf("Inconsistent results.\n");
    }

    free(arr);
    return 0;
}
