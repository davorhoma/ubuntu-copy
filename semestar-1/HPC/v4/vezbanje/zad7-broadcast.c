#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int podatak;
    if (rank == 0) {
        podatak = 100;
        printf("Process %d salje svima podatak %d\n", rank, podatak);
        for (int i=1; i<size; i++) {
            MPI_Send(&podatak, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } 
    else {
        MPI_Recv(&podatak, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d prima poruku %d od root procesa\n", rank, podatak);
    }

    MPI_Finalize();
    
    return 0;
}