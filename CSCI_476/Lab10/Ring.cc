#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include <mpi.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

const int MAX_STRING = 80;

int 
main ( int argc, char* argv[] )
{
  MPI_Init ( &argc, &argv );
  int numProcesses;
  MPI_Comm_size ( MPI_COMM_WORLD, &numProcesses );
  int rank;
  MPI_Comm_rank ( MPI_COMM_WORLD, &rank );

  char str [ MAX_STRING ] = { 0 };
  int next_node = ( rank + 1 == numProcesses ) ? 0 : rank + 1;

  if ( rank != 0 )
  {
    MPI_Recv ( str, MAX_STRING, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, 
      MPI_STATUS_IGNORE );

    MPI_Send ( str, strlen ( str ) + 1, MPI_CHAR, next_node, 0, MPI_COMM_WORLD );
  }
  else
  {
    cout << endl;
    cin.getline( str, MAX_STRING, '\n' );
    cout << endl;

    MPI_Send ( str, strlen ( str ) + 1, MPI_CHAR, next_node, 0, MPI_COMM_WORLD);

    MPI_Recv ( str, MAX_STRING, MPI_CHAR, numProcesses - 1, 0, 
        MPI_COMM_WORLD, MPI_STATUS_IGNORE );

    cout << str << endl;
  }

  MPI_Finalize ();
  return EXIT_SUCCESS;
}
