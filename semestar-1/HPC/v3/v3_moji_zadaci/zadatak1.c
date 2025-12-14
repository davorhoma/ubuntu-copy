#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int wrank, wsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    
    
    MPI_Comm newComm;
    int rank, size;
    MPI_Comm_split(MPI_COMM_WORLD, wrank % 2, wrank, &newComm);
    MPI_Comm_rank(newComm, &rank);
    MPI_Comm_size(newComm, &size);
    printf("MPI_COMM_WORLD rank: %d/%d - ncomm rank: %d/%d\n", wrank, wsize, rank, size);
    // printf("MPI_newComm: %d/%d\n", rank, size);

    MPI_Comm_free(&newComm);
    MPI_Finalize();
}