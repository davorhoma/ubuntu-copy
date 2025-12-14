#include <stdio.h>

#include "mpi.h"

// int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm *newcomm);

int main(int argc, char *argv[]) {

    int wsize, wrank, nsize, nrank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);

    MPI_Comm ncomm;

    MPI_Comm_split(MPI_COMM_WORLD, wrank % 2, wrank, &ncomm);

    MPI_Comm_size(ncomm, &nsize);
    MPI_Comm_rank(ncomm, &nrank);

    printf("MPI_COMM_WORLD rank: %d/%d - ncomm rank: %d/%d\n", wrank, wsize, nrank, nsize);

    MPI_Comm_free(&ncomm);
    MPI_Finalize();

    return 0;
}