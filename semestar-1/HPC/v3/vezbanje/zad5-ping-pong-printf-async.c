#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define PING_PONG_LIMIT 10

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int counter = 0;
    int partner_rank = (rank + 1) % 2;
    MPI_Request send_request;
    int has_sent = 0;
    while (counter < PING_PONG_LIMIT) {
        if (counter % 2 == rank) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

            if (has_sent) {
                MPI_Wait(&send_request, MPI_STATUS_IGNORE);
            }
            char send_message[60];
            sprintf(send_message, "p%d sent ping_pong_count to p%d and incremented it to %d.\n", rank, partner_rank, counter);
            MPI_Isend(send_message, strlen(send_message) + 1, MPI_CHAR, 2, counter, MPI_COMM_WORLD, &send_request);
            has_sent = 1;
        } else if ((counter + 1) % 2 == rank) {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            char received_message[60];
            counter++;
            // MPI_Request receive_request;
            // MPI_Irecv(received_message, 60, MPI_CHAR, (counter - 1) % 2, counter, MPI_COMM_WORLD, &receive_request);
            MPI_Recv(received_message, 60, MPI_CHAR, (counter - 1) % 2, counter, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // MPI_Wait(&receive_request, MPI_STATUS_IGNORE);
            printf("%s", received_message);
        }
    }

    MPI_Finalize();
    
    return 0;
}