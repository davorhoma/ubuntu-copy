#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Comm newComm;
    MPI_Comm_split(MPI_COMM_WORLD, world_rank % 2, world_rank, &newComm);

    int rank, size;
    MPI_Comm_rank(newComm, &rank);
    MPI_Comm_size(newComm, &size);

    printf("World rank: %d/%d, new comm rank: %d/%d\n", world_rank, world_size, rank, size);

    MPI_Comm_free(&newComm);
    MPI_Finalize();

    return 0;
}