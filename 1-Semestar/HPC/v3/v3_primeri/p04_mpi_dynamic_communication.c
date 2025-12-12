#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        time_t t;
        srand((unsigned) time(&t));
        int size = rand() % 10 + 1;
        char *message = (char *) calloc(size + 1, sizeof(char));

        for (int i = 0; i < size; i++) {
            message[i] = 'a';
        }
    
        MPI_Send(message, size + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        free(message);
    } else if (rank == 1) {
        MPI_Status status; 
        int size;

        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &size);

        printf("Velicina poruke u karakterima: %d\n", size);

        char *message = (char *) malloc(size * sizeof(char));
        MPI_Recv(message, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Primljena poruka: %s.\n", message);
    }

    MPI_Finalize();

    return 0;
}