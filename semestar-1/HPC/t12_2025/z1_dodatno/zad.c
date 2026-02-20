#include <omp.h>
#include <stdio.h>

/**
 * Kurirska sluzba
 *
 * Kurirska sluzba obradjuje N posiljaka tokom jedne smene.
 * U smeni radi BROJ_KURIRA kurira. Svi oni raznose pakete po zonama.
 * Cena paketa zavisi od SEED faktora, zone, i tezine samog paketa.
 * Ukoliko tezina predje odredjeni limit (LIMIT_GRAMA), to se belezi u izvestaj
 * i na takve pakete se dobija dodatna zarada (PENALTY_DIN).
 *
 * Na kraju smene potrebno je generisati potpis smene.
 * On zavisi od dnevnog kljuca za tu smenu (simulacija velike kolicine posla,
 * nije preterano bitno sta tacno se desava), i poslednjeg skeniranog koda u
 * smeni.
 *
 * Dodatne napomene:
 * - BROJ_POSILJAKA, BROJ_KURIRA, i KEY_WORK mozete menjati radi brzeg izvrsenja
 * zadatka
 * - sam nacin racunanja mase i zone nije od preteranog znacaja, `gen_mass`,
 * `gen_zone`, `mix31`, `napravi_scan_code` apsolutno ne morate otvarati, samo
 * su pomocne.
 * - u funkciji `izracunaj_dnevni_kljuc` obratiti paznju
 * da li je racunanje dnevnog kljuca pogodno za paralelizaciju.
 * - za funkciiju `potpis_izvestaja` bitno je samo *od cega zavisi*
 * (dakle koji su parametri) ne i kako tacno radi.
 */

#define BROJ_POSILJAKA 100000000
#define BROJ_KURIRA 8
#define SEED 123

#define LIMIT_GRAMA 5000
#define PENALTY_DIN 200

#define BASE_Z0 120
#define BASE_Z1 180
#define BASE_Z2 260

#define PERKG_Z0 80
#define PERKG_Z1 110
#define PERKG_Z2 170

#define KEY_WORK 10000000

typedef struct {
    long long overCnt;
    long long totalRevenue;
    int lastScanCode;
    int dailyKey;
    int reportSignature; // zavisi od dailyKey + lastScanCode
} izvestajSmene;

int gen_mass(int seed, int i) {
    long long x = (long long)seed * 1664525LL + 1013904223LL +
                  2654435761LL * (long long)i;
    int r = (int)(x % 9900LL);
    if (r < 0)
        r += 9900;
    return r + 100; // 100..9999
}

int gen_zone(int seed, int i) {
    long long x = ((long long)seed ^ ((long long)i * 1103515245LL)) + 12345LL;
    int r = (int)(x % 3LL);
    if (r < 0)
        r += 3;
    return r; // 0..2
}

long long cena_posiljke(int zona, int masaGr, int limitGr, int penaltyDin) {
    int kg = (masaGr + 999) / 1000;

    int base = (zona == 0) ? BASE_Z0 : (zona == 1) ? BASE_Z1 : BASE_Z2;
    int per = (zona == 0) ? PERKG_Z0 : (zona == 1) ? PERKG_Z1 : PERKG_Z2;

    long long price = (long long)base + (long long)per * (long long)kg;
    if (masaGr > limitGr)
        price += (long long)penaltyDin;
    return price;
}

int mix31(int a) {
    long long x = (long long)(a & 0x7fffffff);
    x ^= (x >> 16);
    x = (x * 2147483629LL + 12345LL) & 0x7fffffffLL;
    x ^= (x >> 13);
    x = (x * 2147483587LL + 54321LL) & 0x7fffffffLL;
    x ^= (x >> 15);
    return (int)(x & 0x7fffffffLL);
}

int napravi_scan_code(int seed, int i, int masaGr, int zona, long long price) {
    long long p = price & 0x7fffffffLL;
    long long h = ((long long)seed) ^ ((long long)i * 1000003LL) ^
                  ((long long)masaGr * 10007LL) ^ ((long long)zona * 97LL) ^ p;
    return mix31((int)(h & 0x7fffffffLL));
}

int izracunaj_dnevni_kljuc(int seed) {
    int x = seed & 0x7fffffff;
    for (int k = 0; k < KEY_WORK; k++) {
        x ^= (x << 13) & 0x7fffffff;
        x ^= (x >> 17);
        x ^= (x << 5) & 0x7fffffff;
        x = mix31(x ^ k); // zavisi od x -> da li je pogodno za paralelizaciju?
    }
    return x & 0x7fffffff;
}

int potpis_izvestaja(int dailyKey, long long overCnt, long long totalRevenue,
                     int lastScanCode) {
    long long a = totalRevenue & 0x7fffffffLL;
    long long b = overCnt & 0x7fffffffLL;
    long long c = (long long)(lastScanCode & 0x7fffffff);

    long long h = (long long)dailyKey ^ a ^ (b * 1009LL) ^ (c * 9176LL);

    return mix31((int)(h & 0x7fffffffLL));
}

izvestajSmene sekvencijalno(void) {
    izvestajSmene iz;
    iz.overCnt = 0;
    iz.totalRevenue = 0;
    iz.lastScanCode = 0;
    iz.dailyKey = 0;
    iz.reportSignature = 0;

    iz.dailyKey = izracunaj_dnevni_kljuc(SEED);

    for (int i = 0; i < BROJ_POSILJAKA; i++) {
        int m = gen_mass(SEED, i);
        int z = gen_zone(SEED, i);

        if (m > LIMIT_GRAMA)
            iz.overCnt += 1;

        long long price = cena_posiljke(z, m, LIMIT_GRAMA, PENALTY_DIN);
        iz.totalRevenue += price;

        // potreban za potpis smene
        iz.lastScanCode = napravi_scan_code(SEED, i, m, z, price);
    }

    iz.reportSignature = potpis_izvestaja(iz.dailyKey, iz.overCnt,
                                          iz.totalRevenue, iz.lastScanCode);
    return iz;
}

izvestajSmene paralelno(void) {
    izvestajSmene iz;
    iz.overCnt = 0;
    iz.totalRevenue = 0;
    iz.lastScanCode = 0;
    iz.dailyKey = 0;
    iz.reportSignature = 0;

    long long overCnt = 0;
    long long totalRevenue = 0;

    int poslednjiKod = 0;

    int seed = SEED;

    int paketaPoKuriru =
        (int)(((double)BROJ_POSILJAKA) / (double)BROJ_KURIRA + 0.999999);

    int dailyKey = 0;

    omp_set_num_threads(BROJ_KURIRA);

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task firstprivate(seed)
            dailyKey = izracunaj_dnevni_kljuc(seed);
        }

        #pragma omp for reduction(+ : totalRevenue, overCnt) lastprivate(poslednjiKod)
        for (int i = 0; i < BROJ_POSILJAKA; i++) {
            int m = gen_mass(seed, i);
            int z = gen_zone(seed, i);
    
            if (m > LIMIT_GRAMA)
                overCnt += 1;
    
            long long price = cena_posiljke(z, m, LIMIT_GRAMA, PENALTY_DIN);
            totalRevenue += price;
    
            poslednjiKod = napravi_scan_code(seed, i, m, z, price);
        }
    }


    iz.dailyKey = dailyKey;
    iz.overCnt = overCnt;
    iz.totalRevenue = totalRevenue;
    iz.lastScanCode = poslednjiKod;
    iz.reportSignature = potpis_izvestaja(iz.dailyKey, iz.overCnt,
                                          iz.totalRevenue, iz.lastScanCode);

    return iz;
}

int main(void) {
    double t0, t1;

    t0 = omp_get_wtime();
    izvestajSmene par = paralelno();
    t1 = omp_get_wtime();
    printf("PAR: overCnt=%lld totalRevenue=%lld lastScanCode=%d dailyKey=%d "
           "signature=%d  time=%lf\n",
           par.overCnt, par.totalRevenue, par.lastScanCode, par.dailyKey,
           par.reportSignature, t1 - t0);

    t0 = omp_get_wtime();
    izvestajSmene sek = sekvencijalno();
    t1 = omp_get_wtime();
    printf("SEK: overCnt=%lld totalRevenue=%lld lastScanCode=%d dailyKey=%d "
           "signature=%d  time=%lf\n",
           sek.overCnt, sek.totalRevenue, sek.lastScanCode, sek.dailyKey,
           sek.reportSignature, t1 - t0);

    return 0;
}
