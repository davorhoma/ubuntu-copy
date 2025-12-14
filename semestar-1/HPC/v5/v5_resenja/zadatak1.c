#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

/**
 *
 *     Full array          What we want
 *                            to send
 * +-----+-----+-----+  +-----+-----+-----+
 * |  0  |  1  |  2  |  |  0  |  1  |  2  |
 * +-----+-----+-----+  +-----+-----+-----+
 * |  3  |  4  |  5  |  |  -  |  4  |  5  |
 * +-----+-----+-----+  +-----+-----+-----+
 * |  6  |  7  |  8  |  |  -  |  -  |  8  |
 * +-----+-----+-----+  +-----+-----+-----+
 *
 * How to extract the lower triangle with an indexed type:
 *
 *
 *        +-------------------------------------- displacement for
 *        |                                       block 2: 2N + 2 elements
 *        |                                               |
 *        +--------------- displacement for               |
 *        |                block 2: N + 1 elements        |
 *        |                       |                       |
 *  displacement for              |                       |
 * block 1: 0 elements            |                       |
 *        |                       |                       |
 *        V                       V                       V
 *        +-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *        |  0  |  1  |  2  |  -  |  4  |  5  |  -  |  -  |  8  |
 *        +-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *         <--------------->       <--------->             <--->
 *              block 1              block 2              block 3
 *             N elements          N-1 elements        N-2 elements
 *
 * In case of 5x5 matrix:
 *
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
        int lengths[N] = {0};
        int displacements[N] = {0};

        MPI_Datatype triangle_type;

        for (size_t i = 0; i < N; i++) {
            lengths[i] = N - i;
            displacements[i] = i * N + i;
        }

        MPI_Type_indexed(N, lengths, displacements, MPI_INT, &triangle_type);
        MPI_Type_commit(&triangle_type);

        int buffer[N][N] = {0};
        int current = 0;
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                buffer[i][j] = current++;
            }
        }

        MPI_Send(buffer, 1, triangle_type, RECEIVER, 0, MPI_COMM_WORLD);

        break;
    }
    case RECEIVER: {
        int received[N * (N + 1) / 2];
        MPI_Recv(&received, N * (N + 1) / 2, MPI_INT, SENDER, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        printf("Received values:\n");
        for (size_t i = 0; i < N * (N + 1) / 2; i++) {
            printf("%d ", received[i]);
        }
        printf("\n");
        break;
    }
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
