/**
 * @author RookieHPC
 * @brief Original source code at https://rookiehpc.org/mpi/docs/mpi_group_intersection/index.html
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * @brief Illustrates how to get the intersection/union/difference of two groups 
 * of processes.
 * 
 * This application is meant to be run with 4 processes. 
 * Compile with: 
 *   -DINTERSECT for intersection,
 *   -DUNION for union, and
 *   with no options for difference.
 * 
 * Group operations can be visualised as follows:
 *
 * +--------------+---+---+---+---+
 * | Processes    | 0 | 1 | 2 | 3 |
 * +--------------+---+---+---+---+
 * | Group A      | X | X | X | X |
 * | Group B      |   | X |   | X |
 * | Intersection |   | X |   | X |
 * | Union        | X | X | X | X |
 * | Difference   | X |   | X |   |
 * +--------------+---+---+---+---+
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    // Check that the application is run with 4 processes.
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4)
    {
        printf("Please run this application with 4 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Get the group from the default communicator
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    // Keep all the processes in the group A, in a random order
    MPI_Group group_a;
    int group_a_processes[4] = {2, 0, 3, 1};
    MPI_Group_incl(world_group, 4, group_a_processes, &group_a);

    // Keep the processes 1 and 3 in the group B
    MPI_Group group_b;
    int group_b_processes[2] = {1, 3};
    MPI_Group_incl(world_group, 2, group_b_processes, &group_b);

    // Get the intersection/union/difference of both groups
    MPI_Group new_group;
    #ifdef INTERSECT
    MPI_Group_intersection(group_a, group_b, &new_group);
    #elif UNION
    MPI_Group_union(group_a, group_b, &new_group);
    #else
    MPI_Group_difference(group_a, group_b, &new_group);
    #endif

    // Get my rank in the world communicator
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Create a communicator made of the processes in the intersection group
    MPI_Comm new_communicator;
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_communicator);
    if(new_communicator == MPI_COMM_NULL)
    {
        // I am not part of the communicator created, so I am not part of the intersection group
        printf("Process %d is not part of the new group.\n", my_rank);
    }
    else
    {
        int new_rank;
        MPI_Comm_rank(new_communicator, &new_rank);
        // I am part of the communicator created, so I am part of the intersection group
        printf("Process %d is part of the new group with rank %d.\n", my_rank, new_rank);
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}