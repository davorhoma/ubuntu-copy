#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define PRVA_PARTIJA {1, 3, 4, 9, 11}
#define VELICINA_PRVA 5

#define DRUGA_PARTIJA {2, 4, 5, 7, 8, 9}
#define VELICINA_DRUGA 6

/**
 * Nizovi definisani u delu iznad se mogu koristiti za inicijalizaciju
 * niza u kodu, koristeći zapis oblika:
 *
 * int neki_niz[VELICINA_PRVA] = PRVA_PARTIJA;
 *
 * (uglaste zagrade mogu ostati i prazne).
 */

int main(int argc, char *argv[])
{

    /**
     * 1. TODO: Inicijalizovati MPI aplikaciju.
     */
    MPI_Init(&argc, &argv);

    /**
     * 2. TODO: Pribaviti rank u svetskom komunikatoru i smestiti ga
     * u promenljivu "svetski_rank"
     */
    int svetski_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &svetski_rank);

    /**
     * 3. TODO: Napraviti koaliciju, tako što će se prvo kreirati
     * grupe za obe partije, koje će se nakon toga spojiti
     * u jednu koalicionu, od koje će se napraviti komunikator.
     *
     * Koraci:
     *  - napraviti grupu od svetskog komunikatora (MPI_Comm_group)
     *  - napraviti grupe od nizova za partije (kreirati dva niza i
     *      inicijalizovati ih makroima nizova; kreirati grupe od
     *      tih nizova korišćenjem odgovarajuće funkcije za
     *      kreiranje grupe)
     *  - spojiti dve grupe u jednu koja će sadržati sve procese
     *      iz obe grupe, bez ponavljanja, tako da druga grupa ima
     *      prioritet u određivanju ranka, korišćenjem odgovarajuće
     *      funkcije za kombinovanje dve grupe
     *  - kreirati komunikator od grupe (MPI_Comm_create_group)
     *
     */
    MPI_Group prva_grupa, druga_grupa, svetska_grupa;
    int prvi_niz[VELICINA_PRVA] = PRVA_PARTIJA;
    int drugi_niz[VELICINA_DRUGA] = DRUGA_PARTIJA;
    MPI_Comm_group(MPI_COMM_WORLD, &svetska_grupa);
    MPI_Group_incl(svetska_grupa, VELICINA_PRVA, prvi_niz, &prva_grupa);
    MPI_Group_incl(svetska_grupa, VELICINA_DRUGA, drugi_niz, &druga_grupa);

    MPI_Group nova_grupa;
    MPI_Group_union(druga_grupa, prva_grupa, &nova_grupa);

    MPI_Comm new_comm;
    MPI_Comm_create_group(MPI_COMM_WORLD, nova_grupa, 0, &new_comm);

    /**
     * 4. TODO: Napisati deo koda koji će izvršavati samo procesi koji pripadaju
     * koalciji. Unutar njega pribaviti rank i veličinu koalicionog
     * komunikatora. Nakon toga, u procesu koji ima rank 0 u koalciji
     * zauzeti memoriju za niz (promenljiva int* niz) od onoliko elemenata
     * koliko ima članova u koalciji, i postaviti mu elemente na vrednosti 1, 2, 3...
     * Promenljiva za niz može biti vidljiva svim procesima, ali se memorija zauzima
     * samo u procesu sa rankom 0 u koaliciji. Za zauzimanje memorije može se koristiti
     * funkcija "malloc" na sledeći način:
     *
     * niz = (int *)malloc(broj_elemenata * sizeof(int))
     *
     * Zatim podeliti taj niz po svim članovima koalicije tako da svaki
     * dobije po jedan element, i to koristeći samo jednu kolektivnu MPI
     * operaciju. Svaki član nakon prijema ispisuje poruku oblika:
     * "Proces {svetski_rank}:{koalicioni_rank}: moja naknada deli se sa koeficijentom {moj_koeficijent}"
     *
     * Na kraju ovog dela koda, u procesu sa rankom 0 u koalciji osloboditi
     * memoriju korišćenjem funkcije free(niz).
     */

    if (new_comm != MPI_COMM_NULL)
    {
        int new_rank, new_size;
        MPI_Comm_rank(new_comm, &new_rank);
        MPI_Comm_size(new_comm, &new_size);

        int *niz;
        if (new_rank == 0)
        {
            niz = (int *)malloc(new_size * sizeof(int));
            for (int i = 1; i <= new_size; i++)
            {
                niz[i] = i;
            }
        }

        int element;
        MPI_Scatter(niz, 1, MPI_INT, &element, 1, MPI_INT, 0, new_comm);

        printf("Proces %d:%d: moja naknada deli se sa koeficijentom %d\n", svetski_rank, new_rank, element);

        if (new_rank == 0)
        {
            free(niz);
        }
    }

    /**
     * 5. TODO: Osloboditi zauzete resurse za grupe i komunikator.
     * Grupe oslobađati unutar if-grananja oblika:
     *
     * if (grupa != MPI_GROUP_NULL) {...funkcija za oslobađanje grupe...}
     *
     * Komunikator oslobađati unutar if-grananja kroz koje će proći samo
     * procesi koji su njegovi članovi.
     */
    if (svetska_grupa != MPI_GROUP_NULL) {
        MPI_Group_free(&svetska_grupa);
    }

    if (prva_grupa != MPI_GROUP_NULL)
    {
        MPI_Group_free(&prva_grupa);
    }

    if (druga_grupa != MPI_GROUP_NULL) {
        MPI_Group_free(&druga_grupa);
    }

    if (nova_grupa != MPI_GROUP_NULL) {
        MPI_Group_free(&nova_grupa);
    }

    if (new_comm != MPI_COMM_NULL) {
        MPI_Comm_free(&new_comm);
    }

    /**
     * 6. TODO: Pozvati funkciju za završetak MPI programa.
     */
    MPI_Finalize();

    return 0;
}