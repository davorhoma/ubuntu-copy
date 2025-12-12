#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int wrank, wsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);

    int partner_rank = (wrank + 1) % wsize;
    int recvToken;
    if (wrank == 0) {
        int token = -1;
        MPI_Send(&token, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
        MPI_Recv(&recvToken, 1, MPI_INT, wsize - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", wrank, recvToken, wsize - 1);
    } else {
        MPI_Recv(&recvToken, 1, MPI_INT, wrank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", wrank, recvToken, wrank - 1);
        MPI_Send(&recvToken, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}