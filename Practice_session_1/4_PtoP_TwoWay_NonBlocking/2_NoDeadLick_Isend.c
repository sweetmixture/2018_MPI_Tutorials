#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 100000000
/* Depending on the size of the send buffer 
 * Standard Blocking Send may act like sync send 
 * and ends up with Dead-Lock
 * Solution -> USE NON-BLOKCING routines */

int main (int argc, char* argv[] )
{
	int rank, numtasks, count;
	
	int* sendbuf;
	int* recvbuf;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Status stat1, stat2;
	MPI_Request req;

	if( rank == 0 )
	{
		sendbuf = (int*)malloc(SIZE*sizeof(int));
		recvbuf = (int*)malloc(SIZE*sizeof(int));
	
		MPI_Isend(sendbuf,SIZE,MPI_INTEGER,1,1313,MPI_COMM_WORLD,&req);
		MPI_Recv(recvbuf,SIZE,MPI_INTEGER,1,1212,MPI_COMM_WORLD,&stat1);
		MPI_Wait(&req,&stat2);
		MPI_Get_count(&stat2,MPI_INTEGER,&count);
		
		/* Recv Info */
		printf("Source: %d\n",stat1.MPI_SOURCE);
		printf("Tag   : %d\n",stat1.MPI_TAG);
		printf("Count : %d\n",count);
		printf("\n");


		free(sendbuf);
		free(recvbuf);
	}
	else
	{
		sendbuf = (int*)malloc(SIZE*sizeof(int));
		recvbuf = (int*)malloc(SIZE*sizeof(int));

		MPI_Isend(sendbuf,SIZE,MPI_INTEGER,0,1212,MPI_COMM_WORLD,&req);
		MPI_Recv(recvbuf,SIZE,MPI_INTEGER,0,1313,MPI_COMM_WORLD,&stat1);
		MPI_Wait(&req,&stat2);

		free(sendbuf);
		free(recvbuf);
	}


	MPI_Finalize();
	return 0;
}
