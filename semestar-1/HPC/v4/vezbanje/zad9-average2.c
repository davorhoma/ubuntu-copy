#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

void generateRandom(int *, int);
float calculateAverage(int *, int);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uneli ste pogresan broj argumenata.\n");
        printf("Primer poziva programa: mpiexec -np 4 ./a.out 4\n");
        return 1;
    }

    srand(time(NULL));
    int n = atoi(argv[1]);

    MPI_Init(&argc, &argv);

    int rank, size, root = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *data;
    if (rank == root) {
        data = (int *) malloc(n * size * sizeof(int));
        generateRandom(data, n * size);
    }

    int *partial_data = (int *) malloc(n * sizeof(int));
    MPI_Scatter(data, n, MPI_INT, partial_data, n, MPI_INT, root, MPI_COMM_WORLD);
    
    float partial_avg = calculateAverage(partial_data, n);

    float avg;
    MPI_Reduce(&partial_avg, &avg, 1, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        avg /= size;

        printf("Average: %.2f\n", avg);
        printf("Calculate entire: %.2f\n", calculateAverage(data, n * size));
        free(data);
    }
    free(partial_data);

    MPI_Finalize();
    
    return 0;
}

void generateRandom(int *data, int size) {
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 100;
        printf("%d ", data[i]);
    }

    printf("\n");
}

float calculateAverage(int *data, int size) {
    float avg = 0;
    for (int i = 0; i < size; i++) {
        avg += data[i];
    }

    return avg / size;
}