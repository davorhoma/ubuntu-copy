/**
 * OpenMPI C program koji demonstrira rad MPI_Alleduce funkcije.
 * 
 * Svaki proces unutar MPI_COMM_WORLD komunikatora pravi po jedan zeton,
 * koji prima vrednost ranka procesa i promenljivu result. Nakon poziva
 * MPI_Allreduce funkcije, 'result' promenljiva svih procesa ce imati 
 * vrednost sume rangova svih procesa.
 * 
 * Ocekivani rezultat:
 *  Svi procesi ispisuju vrednost promenljive 'result', 
 *  koja je jednaka sumi rangova svih procesa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int token = rank, result;
    MPI_Allreduce(&token, &result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Proces %d: result = %d.\n", rank, result);

    MPI_Finalize();

    return 0;
}