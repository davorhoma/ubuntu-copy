/**
 * MPI C implementacija sinhrone komunikacije izmedju dva MPI procesa.
 * Proces 0 salje poruku tipa MPI_INT procesu 1. Duzina poruke je 1.
 */

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        int message = 1;
        printf("Proces %d salje poruku procesu %d.\n", rank, 1);
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        int message = 5;
        printf("Proces %d treba da primi poruku od procesa %d.\n", rank, 0);
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, NULL);
        printf("Proces %d primio poruku %d od procesa %d.\n", rank, message, 0);
    }

    MPI_Finalize();

    return 0;
}