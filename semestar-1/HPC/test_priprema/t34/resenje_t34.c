#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define PRVA_PARTIJA { 1, 3, 4, 9, 11 }
#define VELICINA_PRVA 5

#define DRUGA_PARTIJA { 2, 4, 5, 7, 8, 9 }
#define VELICINA_DRUGA 6

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int svetski_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &svetski_rank);

    MPI_Group svetska_grupa;
    MPI_Comm_group(MPI_COMM_WORLD, &svetska_grupa);


    int rankovi_prva[VELICINA_PRVA] = PRVA_PARTIJA;
    MPI_Group grupa_prva;
    MPI_Group_incl(svetska_grupa, VELICINA_PRVA, rankovi_prva, &grupa_prva);


    int rankovi_druga[VELICINA_DRUGA] = DRUGA_PARTIJA;
    MPI_Group grupa_druga;
    MPI_Group_incl(svetska_grupa, VELICINA_DRUGA, rankovi_druga, &grupa_druga);
    

    MPI_Group grupa_koalicija;
    MPI_Group_union(grupa_druga, grupa_prva, &grupa_koalicija);

    MPI_Comm komunikator_koalicija;
    MPI_Comm_create_group(MPI_COMM_WORLD, grupa_koalicija, 0, &komunikator_koalicija);

    if (komunikator_koalicija != MPI_COMM_NULL) {
        int rank_koalicija;
        int velicina_koalicija;

        MPI_Comm_rank(komunikator_koalicija, &rank_koalicija);
        MPI_Comm_size(komunikator_koalicija, &velicina_koalicija);
        int *koeficijenti;
        int moj_koeficijent;

        if(rank_koalicija == 0 ) {
            koeficijenti = (int *)malloc(velicina_koalicija * sizeof(int));
            for (int i = 0; i < velicina_koalicija; i++) {
                koeficijenti[i] = i + 1;
            }
        }

        MPI_Scatter(koeficijenti, 1, MPI_INT, &moj_koeficijent, 1, MPI_INT, 0, komunikator_koalicija);
        printf("Proces %d:%d: moja naknada deli se koeficijentom %d\n", svetski_rank, rank_koalicija, moj_koeficijent);

        if (rank_koalicija == 0) {
            free(koeficijenti);
        }
    }

    MPI_Group_free(&svetska_grupa);

    if (grupa_prva != MPI_GROUP_NULL) {
        MPI_Group_free(&grupa_prva);
    }

    if (grupa_druga != MPI_GROUP_NULL) {
        MPI_Group_free(&grupa_druga);
    }

    if (grupa_koalicija != MPI_GROUP_NULL) {
        MPI_Group_free(&grupa_koalicija);
    }

    if (komunikator_koalicija != MPI_COMM_NULL) {
        MPI_Comm_free(&komunikator_koalicija);
    }
    

    MPI_Finalize();
}