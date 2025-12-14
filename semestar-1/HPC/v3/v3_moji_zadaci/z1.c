#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int wsize, wrank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);

    MPI_Comm newComm;
    MPI_Comm_split(MPI_COMM_WORLD, wrank % 2, wrank, &newComm);
    
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    printf("MPI_COMM_WORLD rank: %d/%d, NewComm rank : %d/%d\n", wrank, wsize, rank, size);

    MPI_Comm_free(&newComm);
    MPI_Finalize();

    return 0;
}