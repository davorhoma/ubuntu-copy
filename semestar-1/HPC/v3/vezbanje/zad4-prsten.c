#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int token;
    int dest_rank = (rank + 1) % size;
    int source_rank = (size + rank - 1) % size;

    if (rank == 0) {
        token = -1;
        MPI_Send(&token, 1, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, source_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received token %d from process %d\n", rank, token, source_rank);
    } else {
        MPI_Recv(&token, 1, MPI_INT, source_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process %d received token %d from process %d\n", rank, token, source_rank);
        MPI_Send(&token, 1, MPI_INT, dest_rank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    
    return 0;
}