#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int wrank, wsize;
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);

    int counter = 0;
    int partner_rank = (wrank + 1) % 2;
    int has_sent = 0;
    MPI_Request send_req;

    while (counter < 10) {
        if (wrank == counter % 2) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

            char message[60];
            sprintf(message, "Process %d sent counter = %d\n", wrank, counter);
            if (has_sent) {
                MPI_Wait(&send_req, MPI_STATUS_IGNORE);
            }

            MPI_Ibsend(&message, strlen(message) + 1, MPI_CHAR, 2, counter,
                       MPI_COMM_WORLD, &send_req);
            has_sent = 1;
        } else if (wrank == (counter + 1) % 2) {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        } else {
            char message[60];
            MPI_Request recv_req;
            counter++;
            MPI_Recv(message, 60, MPI_CHAR, (counter - 1) % 2, counter,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // MPI_Irecv(&message, 60, MPI_CHAR, (counter - 1) % 2, counter,
            //           MPI_COMM_WORLD, &recv_req);

            printf("Received %s", message);
        }
    }

    MPI_Finalize();
}