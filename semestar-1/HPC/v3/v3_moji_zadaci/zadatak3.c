#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int wrank, wsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wsize);

    if (wsize != 3) {
        printf("Wsize treba da bude 3\n");
        return 1;
    }

    int counter = 0;
    int partner_rank = (wrank + 1) % 2;
    while (counter < 10) {
        if (wrank == counter % 2) {
            counter++;
            MPI_Send(&counter, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);

            char send_str[60];
            sprintf(send_str, "p%d sent ping_pong_count to p%d and incremented it to %d.\n", wrank, partner_rank, counter);
            printf("Sending %d chars\n", (int)strlen(send_str)+1);
            MPI_Ssend(send_str, strlen(send_str)+1, MPI_CHAR, 2, counter, MPI_COMM_WORLD);
        } else if (wrank == (counter + 1) % 2) {
            MPI_Recv(&counter, 1, MPI_INT, partner_rank, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        } else {
            char recv_str[60];
            counter++;
            MPI_Recv(recv_str, 60, MPI_CHAR, (counter - 1) % 2,
                     counter, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", recv_str);
        }
    }

    MPI_Finalize();
}