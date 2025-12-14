/**
 * OpenMPI program koji demonstrira rad MPI_Scatter funkcije.
 * 
 * Korenski proces (odredjen vrednoscu promenljive 'root') generise niz 'data' duzine 'datalen'
 * elemenata, pocevsi od vrednosti 0, pa do datalen-1. Vrednosti elemenata niza se dalje dele
 * procesima gde svaki proces dobija 'datalen / size' elemenata originalnog niza (size je broj
 * procesa u MPI_COMM_WORLD komunikatoru).
 * 
 * Ocekivani rezultat (za originalni niz duzine 8 i 4 procesa):
 *  proces 0 dobija elemente 0, 1
 *  proces 1 dobija elemente 2, 3
 *  proces 2 dobija elemente 4, 5
 *  proces 3 dobija elemente 6, 7
 *  
 * Pretpostavka:
 *  Program ce biti pozvan sa vrednoscu 1, 2, 4 ili 8 za opciju -np.
 * 
 * Napomena:
 *  Ispis moze biti u proizvoljnom redosledu.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, root = 0, datalen = 8;  // mozete menjati vrednosti za root i datalen,
                                            // ali i nakon promene datalen mora biti deljivo brojem
                                            // procesa inace primer nece raditi dobro
                                            // 'root' mora imati vrednost ranka nekog od postojecih
                                            // procesa

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *data = NULL;                       // niz koji sadrzi sve podatke
    int *partial_data = NULL;               // niz koji ce sadrzati delove niza 'data' nakon scatter poziva
    int piecelen = datalen / size;          // svaki proces dobija istu kolicinu podataka
    if (rank == root) {                     // samo proces koji deli podatke inicijalizuje niz 'data'
        data = (int *) malloc(sizeof(int) * datalen);
        for (int i = 0; i < datalen; i++) {
            data[i] = i;
        }
        assert(data != NULL);
    }
    partial_data = (int *) malloc(sizeof(int) * piecelen);
    assert(partial_data != NULL);

    MPI_Scatter(data, piecelen, MPI_INT, partial_data, piecelen, MPI_INT, root, MPI_COMM_WORLD);

    for (int i = 0; i < piecelen; i++) {
        printf("Proces %d dobio element %d.\n", rank, partial_data[i]);
    }
    free(partial_data);
    free(data);

    MPI_Finalize();

    return 0;
}