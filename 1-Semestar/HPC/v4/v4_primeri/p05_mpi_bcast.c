#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int token;
    if (rank == root) token = 123;
    printf("Vrednost zetona procesa %d je %d.\n", rank, token);     // Zeton svakog procesa koji nije root proces neinicijalizovan.
    MPI_Barrier(MPI_COMM_WORLD);                                    // Ne mora da se navodi pre MPI_Bcast, navedeno je samo da
                                                                    // bi svi procesi ispisali svoje vrednosti zetona pre nego se odradi
                                                                    // MPI_Bcast, da se ispisi nakon pre i nakon primanja zetona ne mesaju.
    MPI_Bcast(&token, 1, MPI_INT, root, MPI_COMM_WORLD);
    printf("Proces %d primio token %d.\n", rank, token);

    MPI_Finalize();

    return 0;
}