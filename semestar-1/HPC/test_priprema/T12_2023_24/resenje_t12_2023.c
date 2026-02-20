#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define GRANICA 124
#define ODLAGANJE_UVECANJA 2 
#define KORAK 10
#define GRANICA_NASUMICNOG_FAKTORA 23

void sekvencijalna_funkcija(int granica, int korak, int odlaganje_uvecanja, int nasumican_faktor) {
    int x = 0, bez_uvecanja = 0, y, y_suma = 0;

    while (x / granica < 1) {

        #ifdef ITER
        printf("x: %d\n", x);
        #endif

        y = x * pow(-1, x) - 3 * (x % nasumican_faktor);
        y_suma += y;

        if (bez_uvecanja == odlaganje_uvecanja) {
            bez_uvecanja = 0;
            x += (odlaganje_uvecanja + 1) * korak;
        }
        else {
            bez_uvecanja++;
        }
    }

    printf("y_suma: %d; poslednje y: %d\n", y_suma, y);
}

void moja_paralelna_funkcija(int granica, int korak, int odlaganje_uvecanja, int nasumican_faktor) {
    int x = 0, bez_uvecanja = 0, y, y_suma = 0;
    int podela;

    int iterations;
    iterations = odlaganje_uvecanja * (odlaganje_uvecanja + 1) * korak;

    // uvecanje * (bez_uvecanja / odlaganje_uvecanja) * iterations = granica;
    // iterations = granica / (uvecanje * (bez_uvecanja / odlaganje_uvecanja));
    iterations = granica * odlaganje_uvecanja / ((odlaganje_uvecanja + 1) * korak * bez_uvecanja);


    int uvecanje = (odlaganje_uvecanja + 1) * korak;

    #pragma omp parallel for firstprivate(x) lastprivate(y) reduction(+ : y_suma)
    for (int i = 0; i < iterations; i++) {
        y = x * pow(-1, x) - 3 * (x % nasumican_faktor);
        y_suma += y;
        
        x += uvecanje * (bez_uvecanja / odlaganje_uvecanja);

        #pragma omp critical
        bez_uvecanja++;
    }

    // #pragma omp parallel for private(x) lastprivate(y) reduction(+ : y_suma)
    // for (int x = 0; x < granica; x += uvecanje * (bez_uvecanja / odlaganje_uvecanja)) {
    //     y = x * pow(-1, x) - 3 * (x % nasumican_faktor);
    //     y_suma += y;

    //     #pragma omp critical
    //     bez_uvecanja++;
    // }

    // while (x / granica < 1) {

    //     #ifdef ITER
    //     printf("x: %d\n", x);
    //     #endif

    //     y = x * pow(-1, x) - 3 * (x % nasumican_faktor);
    //     y_suma += y;

    //     if (bez_uvecanja == odlaganje_uvecanja) {
    //         bez_uvecanja = 0;
    //         x += (odlaganje_uvecanja + 1) * korak;
    //     }
    //     else {
    //         bez_uvecanja++;
    //     }
    // }

    printf("y_suma: %d; poslednje y: %d\n", y_suma, y);
}

void paralelna_funkcija(int granica, int korak, int odlaganje_uvecanja, int nasumican_faktor) {
    int x = 0, y, y_suma = 0;
    int kompenzacija_odlaganja = odlaganje_uvecanja + 1;

    int broj_iteracija = granica / korak + 1;
    int ostatak = broj_iteracija % kompenzacija_odlaganja;
    if (ostatak != 0) {
        broj_iteracija += kompenzacija_odlaganja - ostatak;
    }


    #pragma omp parallel for private(x) lastprivate(y) reduction(+ : y_suma) 
    for (int i = 0; i < broj_iteracija; i++) {
        x = (i / kompenzacija_odlaganja) * kompenzacija_odlaganja * korak;

        #ifdef ITER
        printf("x: %d\n", x);
        #endif

        y = x * pow(-1, x) - kompenzacija_odlaganja * (x % nasumican_faktor);
        y_suma += y;
    }

    printf("y_suma: %d; poslednje y: %d\n", y_suma, y);

}

int main(int argc, char* argv[]) {

    time_t vreme = time(0);
    srand(vreme);
    int nasumican_faktor = rand() % GRANICA_NASUMICNOG_FAKTORA + 1;

    printf("\n--------------------- SEKVENCIJALNA FUNKCIJA ---------------------\n");
    sekvencijalna_funkcija(GRANICA, KORAK, ODLAGANJE_UVECANJA, nasumican_faktor);
    printf("------------------------------------------------------------------\n\n");

    printf("--------------------- PARALELNA FUNKCIJA ---------------------\n");
    paralelna_funkcija(GRANICA, KORAK, ODLAGANJE_UVECANJA, nasumican_faktor);
    printf("--------------------------------------------------------------\n\n");

    printf("--------------------- MOJA PARALELNA FUNKCIJA ---------------------\n");
    moja_paralelna_funkcija(GRANICA, KORAK, ODLAGANJE_UVECANJA, nasumican_faktor);
    printf("--------------------------------------------------------------\n\n");
}