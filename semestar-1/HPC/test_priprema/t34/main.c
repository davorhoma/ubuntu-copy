#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>


#define PRVA_PARTIJA { 1, 3, 4, 9, 11 }
#define VELICINA_PRVA 5

#define DRUGA_PARTIJA { 2, 4, 5, 7, 8, 9 }
#define VELICINA_DRUGA 6

/**
 * Nizovi definisani u delu iznad se mogu koristiti za inicijalizaciju
 * niza u kodu, koristeći zapis oblika:
 * 
 * int neki_niz[VELICINA_PRVA] = PRVA_PARTIJA;
 * 
 * (uglaste zagrade mogu ostati i prazne).
*/


int main(int argc, char* argv[]) {

    /**
     * 1. TODO: Inicijalizovati MPI aplikaciju.
    */

    /**
     * 2. TODO: Pribaviti rank u svetskom komunikatoru i smestiti ga 
     * u promenljivu "svetski_rank"
    */
    int svetski_rank;


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

    /**
     * 5. TODO: Osloboditi zauzete resurse za grupe i komunikator.
     * Grupe oslobađati unutar if-grananja oblika:
     * 
     * if (grupa != MPI_GROUP_NULL) {...funkcija za oslobađanje grupe...}
     * 
     * Komunikator oslobađati unutar if-grananja kroz koje će proći samo
     * procesi koji su njegovi članovi.
    */

    /**
     * 6. TODO: Pozvati funkciju za završetak MPI programa.
    */
}