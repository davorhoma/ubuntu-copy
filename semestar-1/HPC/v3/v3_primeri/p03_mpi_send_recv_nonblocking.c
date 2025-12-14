#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Request send_request;
        char *message = "Zdravo!";

        MPI_Issend(message, 8, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &send_request);
        printf("Proces %d inicirao slanje poruke.\n", rank);

        printf("Proces %d radi nesto drugo dok se poruka salje...\n", rank);

        int flag = 0;
        MPI_Test(&send_request, &flag, NULL);
        if (flag != 0) {
            printf("Proces %d je poslao poruku. Sadrzaj bafera ce biti postavljen na \"!ovardZ\".\n", rank);
            message = "!ovardZ";
        } else {
            printf("Proces %d jos nije poslao poruku, pa ona nece biti prepisana.\n", rank);
        }
        printf("Proces %d trenutni tekst poruke: %s\n", rank, message);
    } else {
        MPI_Request receive_request;
        char message[8];

        // Immediate receive. Samo se inicira prijem poruke od procesa 0 iz MPI_COMM_WORLD
        // komunikatora, ali se ne ceka da poruka bude primljena. Nastavlja se dalje sa
        // izvrsavanjem dok sve dok poruka koju je poslao primalac ne bude neophodna za
        // dalji rad (u ovom slucaju to je do linije kada treba ispisati primljenu poruku).
        MPI_Irecv(message, 8, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &receive_request);
        printf("Proces %d inicirao primanje poruke.\n", rank);

        printf("Proces %d radi nesto drugo dok se poruka prima...\n", rank);

        // MPI_Wait je blokirajuca operacija. Nakon sto se zavrsi u message baferu primaoca
        // ce biti poslata poruka. Do ovog trenutka je poruka mogla vec biti kopirana u bafer,
        // ali nema garancije za to.
        // Ukoliko je potrebna neka od informacija status strukture (npr. broj primljenih
        // karaktera), umesto NULL treba proslediti instancu MPI_Status strukture cija ce
        // polja biti popunjena po zavrsetku poziva.
        MPI_Wait(&receive_request, NULL);
        printf("Proces %d primio poruku: \"%s\"\n", rank, message);
    }

    MPI_Finalize();

    return 0;
}