/**
 * OpenMPI C program koji demonstrira rad MPI_Gather funkcije.
 * 
 * Svi procesi generisu niz 'partial_data' duzine 'piecelen' i svaki od nizova inicijalizuju 
 * vrednostima od 'piecelen' do 1 dodatim na vrednost ranka procesa. 
 * Pozivom MPI_Gather funkcije vrednosti se iz 'partial_data' nizova svih procesa 
 * kopiraju u 'data' niz korenskog procesa po rastucoj vrednosti ranka procesa.
 * 
 * Ocekivani rezultat (za 'partila_data' nizove duzine 2 elementa i 4 procesa):
 *  proces 0, partial_data = [2, 1]
 *  proces 1, partial_data = [3, 2]
 *  proces 2, partial_data = [4, 3]
 *  proces 3, partial_data = [5, 4]
 *  proces 0, data = [2, 1, 3, 2, 4, 3, 5, 4]
 *  
 * Pretpostavka:
 *  Program ce biti pozvan sa vrednoscu 1, 2, 4 ili 8 za opciju -np.
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

    int *data = NULL;                       // niz koji ce nakon poziva gather funkcije sadrzati sve podatke iz partial_data nizova
    int *partial_data = NULL;               // nizovi koje imaju svi procesi
    int piecelen = datalen / size;          // svaki proces dobija istu kolicinu podataka

    partial_data = (int *) malloc(sizeof(int) * piecelen);
    assert(partial_data != NULL);

    // svaki proces inicijalizuje svoju instancu niza vrednostima od
    // piecelen-1 do 0 (tim redosledom)
    for (int i = 0; i < piecelen; i++) {
        partial_data[i] = rank + piecelen - i;
    }

    if (rank == root) {                     // samo korenski proces alocira prostor za niz koji ce sadrzati sve podatke
        data = (int *) malloc(sizeof(int) * datalen);
        assert(data != NULL);
    }

    MPI_Gather(partial_data, piecelen, MPI_INT, data, piecelen, MPI_INT, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("Rezultujuci niz nakon poziva MPI_Gather funkcije: ");
        for (int i = 0; i < datalen; i++) {
            printf("%d ", data[i]);
        } printf("\n");
        free(data);
    }
    free(partial_data);

    MPI_Finalize();

    return 0;
}