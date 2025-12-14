/**
 * @author RookieHPC
 * @brief Original source code at https://rookiehpc.org/mpi/docs/mpi_type_contiguous/index.html
 * @details The original source code is slightly altered, in order to use three instead of two
 * contiguous integers, and in order to send and receive different datatypes.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * @brief Illustrates how to create a contiguous MPI datatype.
 * @details This program is meant to be run with 2 processes: a sender and a
 * receiver. These two MPI processes will exchange a message made of three
 * integers. To that end, they each create a datatype representing that layout.
 * They then use this datatype to express the message type exchanged.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Get the number of processes and check only 2 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 2)
    {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get my rank and, if I am the sender, create the datatype

    enum role_ranks { SENDER, RECEIVER };
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Datatype triple_int_type;
    if (my_rank == SENDER)
    {
        MPI_Type_contiguous(3, MPI_INT, &triple_int_type);
        MPI_Type_commit(&triple_int_type);
    }

    // Do the corresponding job
    switch(my_rank)
    {
        case SENDER:
        {
            // Send the message
            int buffer_sent[3] = {123, 456, 789};
            printf("MPI process %d sends values %d, %d and %d.\n", my_rank, buffer_sent[0], buffer_sent[1], buffer_sent[2]);
            MPI_Send(&buffer_sent, 1, triple_int_type, RECEIVER, 0, MPI_COMM_WORLD);
            break;
        }
        case RECEIVER:
        {
            // Receive the message
            int received[3];
            MPI_Recv(&received, 3, MPI_INT, SENDER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("MPI process %d received values: %d, %d and %d.\n", my_rank, received[0], received[1], received[2]);
            break;
        }
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
