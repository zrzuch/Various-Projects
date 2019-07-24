#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <mpi.h>

const int MAX_STRING = 100;

int 
main (int argc, char* argv[])
{
  MPI_Init (&argc, &argv);
  int numProcesses;
  MPI_Comm_size (MPI_COMM_WORLD, &numProcesses);
  int rank;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);

  char greeting[MAX_STRING];
  if (rank != 0)
  {
    sprintf (greeting, "Greetings from process %d of %d!",
	     rank, numProcesses);
    MPI_Send (greeting, strlen (greeting) + 1, MPI_CHAR,
	      0, 0, MPI_COMM_WORLD);
  }
  else
  {
    printf ("Greetings from process %d of %d!\n",
	    rank, numProcesses);
    for (int q = 1; q < numProcesses; ++q)
    {
      MPI_Recv (greeting, MAX_STRING, MPI_CHAR,
		q, 0, 
		MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf ("%s\n", greeting);
    }  
  }

  MPI_Finalize ();

  return EXIT_SUCCESS;
}
