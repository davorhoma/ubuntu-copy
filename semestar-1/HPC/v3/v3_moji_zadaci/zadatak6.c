#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    const int MAX_COUNT = 999;

    MPI_Init(&argc, &argv);

    int wrank, wsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);

    int counter = 0;
    int partner_rank = (wrank + 1) % 2;
    MPI_Request send_req;
    int has_sent = 0;

    while (counter < MAX_COUNT) {
        if (wrank == counter % 2) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            // printf("Poslao %d\n", counter);

            char send_message[60];
            sprintf(send_message, "p%d sent counter to p%d and incremented it to %d.", wrank, partner_rank, counter);

            // if (has_sent) {
            //     MPI_Wait(&send_req, MPI_STATUS_IGNORE);
            // }

            MPI_Send(send_message, strlen(send_message) + 1, MPI_CHAR, 2, counter, MPI_COMM_WORLD);
            has_sent = 1;
            // printf("Poslao %s\n", send_message);
        } else if (wrank == (counter + 1) % 2) {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            MPI_Status status;
            counter++;
            int size;
            // printf("Proces p%d ceka na poruku: \n", wrank);
            MPI_Probe((counter - 1) % 2, counter, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_CHAR, &size);

            // printf("Velicina poruke u karakterima: %d\n", size);

            char *recv_message = (char *) malloc(size * sizeof(char));
            MPI_Recv(recv_message, size, MPI_CHAR, (counter -1) % 2, counter, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("Primio: %s\n", recv_message);
        }
    }

    MPI_Finalize();
}