#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int counter = 0;
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int partner_rank = (rank + 1) % 2;
    while (counter < 5) {
        if (counter % 2 == rank) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("p%d sent ping_pong_count to p%d and incremented it to %d.\n", rank, partner_rank, counter);
        } else {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("p%d received ping_pong_count %d from p%d\n", rank, counter, partner_rank);
            
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("p%d sent ping_pong_count to p%d and incremented it to %d.\n", rank, partner_rank, counter);
        }
    }

    MPI_Finalize();

    return 0;
}