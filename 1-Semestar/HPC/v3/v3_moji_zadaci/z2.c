#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int count = 0;
    // int sent = 0;
    int partner_rank = (rank + 1) % 2;
    while (count < 10) {
        if (rank == count % 2) {
        // if (rank % 2 == 0) {
            // if (sent) {
            //     MPI_Recv(&count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
            // }

            count++;
            MPI_Send(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("Proces %d poslao %d\n", rank, count);
            // sent = 1;
        } else {
            MPI_Recv(&count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, NULL);
            printf("Proces %d primio %d\n", rank, count);
            // count++;
            // MPI_Send(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}