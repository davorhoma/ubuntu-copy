#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

float compute_avg(int *array, int num_elements);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    MPI_Init(&argc, &argv);

    if (argc != 2) {
        printf("Niste uneli odgovarajuci broj argumenata.\n");
        printf("Primer poziva: mpiexec -np 4 ./a.out 8\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size, root = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *data;
    int n = atoi(argv[1]);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root)
    {
        printf("Vrednost n: %d\n", n);
        data = (int *)malloc(n * size * sizeof(int));

        for (int i = 0; i < n*size; i++) {
            data[i] = rand() % 100;
            printf("%d", data[i]);
            if (i != n*size - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int *partial_data = (int *) malloc(n * sizeof(int));
    MPI_Scatter(data, n, MPI_INT, partial_data, n, MPI_INT, root, MPI_COMM_WORLD);

    float partial_average = 0;
    for (int i = 0; i < n; i++) {
        partial_average += partial_data[i];
    }
    partial_average /= n;

    float *avgs;
    if (rank == root) {
        avgs = (float *) malloc(size * sizeof(float));
    }
    MPI_Gather(&partial_average, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

    if (rank == root) {
        float result = 0;
        for (int i = 0; i < size; i++) {
            result += avgs[i];
        }

        result /= size;
        printf("Final average is: %.2f\n", result);
        printf("Final average is: %.2f\n", compute_avg(data, n*size));
    }

    if (rank == root) {
        free(data);
        free(avgs);
    }
    free(partial_data);

    MPI_Finalize();

    return 0;
}

float compute_avg(int *array, int num_elements) {
  float sum = 0.f;
  int i;
  for (i = 0; i < num_elements; i++) {
    sum += array[i];
  }
  return sum / num_elements;
}