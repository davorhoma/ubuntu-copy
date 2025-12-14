// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Ping pong example with MPI_Send and MPI_Recv. Two processes ping pong a
// number back and forth, incrementing it until it reaches a given value.
//
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  const int PING_PONG_LIMIT = 10;

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We are assuming at least 2 processes for this task
  if (world_size != 3) {
    fprintf(stderr, "World size must be three for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int ping_pong_count = 0;
  int partner_rank = (world_rank + 1) % 2;
  int has_sent = 0;
  MPI_Request send_req;
  
  while (ping_pong_count < PING_PONG_LIMIT) {
    if (world_rank == ping_pong_count % 2) {
      // Increment the ping pong count before you send it
      ping_pong_count++;
      MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
      char send_str[60];
      sprintf(send_str, "p%d sent ping_pong_count to p%d and incremented it to %d.\n",
             world_rank, partner_rank, ping_pong_count);
      if(has_sent) {
        MPI_Wait(&send_req, MPI_STATUS_IGNORE);
      } 
      MPI_Isend(send_str, strlen(send_str)+1, MPI_CHAR, 2, ping_pong_count, MPI_COMM_WORLD, &send_req);
      has_sent = 1;
    } else if (world_rank == (ping_pong_count + 1) % 2) {
      MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
    } else {
      char recv_str[60];
      ping_pong_count++;
      MPI_Request recv_req;
      MPI_Recv(recv_str, 60, MPI_CHAR, (ping_pong_count - 1) % 2, ping_pong_count, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //   MPI_Irecv(recv_str, 60, MPI_CHAR, (ping_pong_count - 1) % 2, ping_pong_count, MPI_COMM_WORLD, &recv_req);
      printf("%s", recv_str);
    }
  }
  MPI_Finalize();
}
