/**
 * OpenMPI C program koji demonstrira rad MPI_Allgather funkcije.
 * 
 * Svaki od procesa iz MPI_COMM_WORLD komunikatora pravi po jedan zeton
 * koji ima vrednost ranka tog procesa (promenljiva 'token'). Posto svaki
 * proces nakon poziva MPI_Allgather funkcije treba da primi tokene svih
 * procesa iz komunikatora, svaki od procesa alocira niz 'data' duzine
 * ukupnog broja procesa u komunikatoru. Nakon poziva allgather funkcije
 * nizovi data svih procesa ce biti popunjeni i to tako sto se vrednosti u
 * nizove upisuju u skladu sa rastucom vrednoscu ranka procesa koji salje
 * vrednost. Nakon sto svaki niz popuni svoj niz 'data', svaki proces u
 * komunikatoru ispisuje vrednosti svog niza.
 * 
 * Ocekivani rezultati (u slucaju pokretanja 4 procesa):
 *  proces 0 -> token=0, data nepoznate vrednosti
 *  proces 1 -> token=1, data nepoznate vrednosti 
 *  proces 2 -> token=2, data nepoznate vrednosti
 *  proces 3 -> token=3, data nepoznate vrednosti
 *  <- nakon MPI_Allgather poziva ->
 *  proces 0 -> token=0, data = [0, 1, 2, 3]
 *  proces 1 -> token=1, data = [0, 1, 2, 3]
 *  proces 2 -> token=2, data = [0, 1, 2, 3]
 *  proces 3 -> token=3, data = [0, 1, 2, 3]
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *data = (int *) malloc(sizeof(int) * size);     // svaki proces alocira prostor za 'size' zetona 
                                                        // (1 svoj, size-1 zetona preostalih procesa iz komunikatora)
    assert(data != NULL);

    int token = rank;
    MPI_Allgather(&token, 1, MPI_INT, data, 1, MPI_INT, MPI_COMM_WORLD);

    // Da bi se sprecilo preplitanje ispisa vise procesa na konzolu, ispisi
    // se vrse sekvencijalno, tako sto vrednost svog niza ispisuje samo jedan
    // proces koji je na redu, dok svi ostali cekaju na barijeri.
    // Ovo usporava izvrsavanje programa, ali u ovom slucaju je bitno jasno 
    // ilustrovati efekat izvrsavanja allgather funkcije, pa se vreme izvrsavanja
    // zanemaruje.
    for (int next_rank = 0; next_rank < size; next_rank++) {
        if (rank == next_rank) {
            printf("Proces %d. Token: %d. Elementi niza procesa: ", next_rank, token);
            for (int j = 0; j < size; j++) {
                printf("%d ", data[j]);
            } printf("\n");
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    free(data);

    MPI_Finalize();

    return 0;
}