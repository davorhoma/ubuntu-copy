#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int partner_rank = (rank + 1) % 2;
    int counter = 0;
    int has_sent = 0;
    MPI_Request send_request;

    while (counter < 999) {
        if (rank == counter % 2) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

            if (has_sent) {
                MPI_Wait(&send_request, MPI_STATUS_IGNORE);
            }

            char send_message[60];
            sprintf(send_message, "p%d sent ping_pong_count to p%d and incremented it to %d.\n", rank, partner_rank, counter);
            MPI_Isend(send_message, strlen(send_message) + 1, MPI_CHAR, 2, counter, MPI_COMM_WORLD, &send_request);
            has_sent = 1;
        } else if (rank == (counter + 1) % 2) {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            counter++;
            MPI_Status status;
            MPI_Probe((counter - 1) % 2, counter, MPI_COMM_WORLD, &status);

            int message_size;
            MPI_Get_count(&status, MPI_CHAR, &message_size);

            // char received_message[message_size];
            char *received_message = (char *) malloc(message_size * sizeof(char));
            MPI_Recv(received_message, message_size, MPI_CHAR, (counter - 1) % 2, counter, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", received_message);

            free(received_message);
        }
    }

    MPI_Finalize();
    
    return 0;
}