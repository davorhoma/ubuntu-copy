#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int wrank, wsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);

    int counter = 0;
    int partner_rank = (wrank + 1) % 2;
    while (counter < 10) {
        if (wrank == counter % 2) {
            counter += 1;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("p%d sent count to p%d and incremented it to %d\n", wrank, partner_rank, counter);
        } else {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("p%d received counter %d from p%d\n", wrank, partner_rank, counter);
        }
    }

    MPI_Finalize();
}