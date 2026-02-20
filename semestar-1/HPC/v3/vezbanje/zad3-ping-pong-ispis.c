#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size != 3) {
        printf("Neispravan broj niti");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int partner_rank = (rank + 1) % 2;
    int counter = 0;
    while (counter < 15) {
        if (counter % 2 == rank) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

            char message[60];
            sprintf(message, "p%d sent ping_pong_count to p%d and incremented it to %d\n", rank, partner_rank, counter);
            MPI_Bsend(message, strlen(message) + 1, MPI_CHAR, 2, counter, MPI_COMM_WORLD);
        } else if ((counter + 1) % 2 == rank) {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            char received_message[60];
            counter++;
            MPI_Recv(&received_message, 60, MPI_CHAR, (counter - 1) % 2, counter, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", received_message);
        }
    }

    MPI_Finalize();
    
    return 0;
}