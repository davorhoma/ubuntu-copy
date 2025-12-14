#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 4

/**
 *
 *
 *         Full array                  What we want
 *                                       to send
 * +-----+-----+-----+-----+    +-----+-----+-----+-----+
 * |  0  |  1  |  2  |  3  |    |  0  |  -  |  -  |  -  |
 * +-----+-----+-----+-----+    +-----+-----+-----+-----+
 * |  4  |  5  |  6  |  7  |    |  4  |  -  |  -  |  -  |
 * +-----+-----+-----+-----+    +-----+-----+-----+-----+
 * |  8  |  9  | 10  | 11  |    |  8  |  -  |  -  |  -  |
 * +-----+-----+-----+-----+    +-----+-----+-----+-----+
 *
 * How to extract a column with a vector type:
 *
 *   distance between the
 *   start of each block: M elements
 *   <----------------------> <---------------------->
 *   |                       |                       |
 *  start of              start of                start of
 *  block 1               block 2                 block 3
 *   |                       |                       |
 *   V                       V                       V
 *   +-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *   |  0  |  -  |  -  |  -  |  4  |  -  |  -  |  -  |  8  |
 *   +-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *    <--->                   <--->                   <--->
 *   block 1                  block 2                 block 3
 *
 * Then just move the starting element and repeat.
 * Block length: 1 element
 *
 * Element: MPI_INT
 **/

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size != 2) {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    enum rank_roles { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    switch (my_rank) {
    case SENDER: {
        MPI_Datatype column_type;
        MPI_Type_vector(N, 1, M, MPI_INT, &column_type);
        MPI_Type_commit(&column_type);

        int buffer[N][M] = {0};
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                buffer[i][j] = i * M + j;
            }
        }

        printf("Process %d: Original Matrix:\n", my_rank);
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                printf("%2d ", buffer[i][j]);
            }
            printf("\n");
        }

        for (size_t i = 0; i < M; i++) {
            MPI_Send(&buffer[0][i], 1, column_type, RECEIVER, 0,
                     MPI_COMM_WORLD);
        }

        break;
    }

    case RECEIVER: {
        int transposed[M][N] = {0};

        for (size_t i = 0; i < M; i++) {
            MPI_Recv(&transposed[i][0], N, MPI_INT, SENDER, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        }

        printf("Process %d: Transposed Matrix:\n", my_rank);
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                printf("%2d ", transposed[i][j]);
            }
            printf("\n");
        }

        break;
    }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}