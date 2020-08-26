#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 100000000
/* Depending on the size of the send buffer 
 * Standard Blocking Send may act like sync send 
 * and ends up with Dead-Lock
 */

int main (int argc, char* argv[] )
{
	int rank, numtasks;
	
	int* sendbuf;
	int* recvbuf;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Status status;

	if( rank == 0 )
	{
		sendbuf = (int*)malloc(SIZE*sizeof(int));
		recvbuf = (int*)malloc(SIZE*sizeof(int));
	
		MPI_Send(sendbuf,SIZE,MPI_INTEGER,1,1313,MPI_COMM_WORLD);
		MPI_Recv(recvbuf,SIZE,MPI_INTEGER,1,1212,MPI_COMM_WORLD,&status);
		
		free(sendbuf);
		free(recvbuf);
	}
	else
	{
		sendbuf = (int*)malloc(SIZE*sizeof(int));
		recvbuf = (int*)malloc(SIZE*sizeof(int));

		MPI_Send(sendbuf,SIZE,MPI_INTEGER,0,1212,MPI_COMM_WORLD);
		MPI_Recv(recvbuf,SIZE,MPI_INTEGER,0,1313,MPI_COMM_WORLD,&status);

		free(sendbuf);
		free(recvbuf);
	}


	MPI_Finalize();
	return 0;
}
