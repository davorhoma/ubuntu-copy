#include <stdio.h>
#include <mpi.h>

/**
 * Primer preuzet sa https://mpitutorial.com/tutorials/introduction-to-groups-and-communicators/
 * Primer pokrenuti sa najmanje 8 procesa.
 * Kompajlirati sa opcijom -DEXCL za korišćenje MPI_Group_excl funkcije.
 * Bez ove opcije, koristiće se MPI_Group_incl.
*/
// 
// 
//

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size < 8) {
        fprintf(stderr, "World size must be at lease 8 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    /**
     * Kreirati grupu od procesa iz komunikatora MPI_COMM_WORLD.
     */ 
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group); 

    int n = 5;
    const int ranks[5] = {0, 1, 4, 6, 7};

    /**
     * Kreirati novu grupu od postojeće, uključivanjem ili isključivanjem
     * određenih procesa.
     */ 
    MPI_Group new_group;
    #ifdef EXCL
    MPI_Group_excl(world_group, 5, ranks, &new_group);
    #else
    MPI_Group_incl(world_group, 5, ranks, &new_group);
    #endif

    /**
     * Kreirati novi komunikator na osnovu starog, koristeći
     * novokreiranu grupu da naznači koji procesi će se naći
     * u novom komunikatoru.
     */ 
    MPI_Comm new_comm;
    MPI_Comm_create_group(MPI_COMM_WORLD, new_group, 0, &new_comm);

    int new_comm_rank = -1, new_comm_size = -1;

    if (MPI_COMM_NULL != new_comm) {
        MPI_Comm_rank(new_comm, &new_comm_rank);
        MPI_Comm_size(new_comm, &new_comm_size);
    }

    int data;

    if (MPI_COMM_NULL != new_comm && new_comm_rank == 0) {
        data = 100;
    }

    /**
     * Izvršiti grupnu operaciju nad procesima iz novog komunikatora.
     */ 
    if (MPI_COMM_NULL != new_comm) {
        MPI_Bcast(&data, 1, MPI_INT, 0, new_comm);
    }
    printf("World rank = %d; new communicator rank = %d; data = %d\n", world_rank, new_comm_rank, data);

    MPI_Group_free(&world_group);

    if (MPI_COMM_NULL != new_comm) {
        MPI_Group_free(&new_group);
        MPI_Comm_free(&new_comm);
    }

    MPI_Finalize();
}