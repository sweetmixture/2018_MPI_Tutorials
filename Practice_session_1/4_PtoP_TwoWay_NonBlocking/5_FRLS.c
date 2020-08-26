#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 100000000

int main ( int argc, char* argv[] )
{
	int rank, numtasks, count;

	int* sendbuf;
	int* recvbuf;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Status stat1, stat2;
	MPI_Request sreq, rreq;

	if( rank == 0 )
	{
		sendbuf = (int*)calloc(SIZE,sizeof(int));
		recvbuf = (int*)calloc(SIZE,sizeof(int));
		
		MPI_Irecv(recvbuf,SIZE,MPI_INTEGER,1,1212,MPI_COMM_WORLD,&rreq);
	//	MPI_Recv(recvbuf,SIZE,MPI_INTEGER,1,1212,MPI_COMM_WORLD,&stat1);	// dead lock
		MPI_Send(&sendbuf[4],SIZE-5,MPI_INTEGER,1,1313,MPI_COMM_WORLD);
		MPI_Wait(&rreq,&stat1);
		
		MPI_Get_count(&stat1,MPI_INTEGER,&count);

		printf("Rank : %d\n",rank);
		printf("Data Count: %d\n",count);
		printf("Source : %d\n",stat1.MPI_SOURCE);
		printf("TAG    : %d\n",stat1.MPI_TAG);

		free(sendbuf);
		free(recvbuf);
	}
	else
	{
		sendbuf = (int*)calloc(SIZE,sizeof(int));
		recvbuf = (int*)calloc(SIZE,sizeof(int));
		

		MPI_Recv(recvbuf,SIZE,MPI_INTEGER,0,1313,MPI_COMM_WORLD,&stat1);
		MPI_Isend(sendbuf,SIZE,MPI_INTEGER,0,1212,MPI_COMM_WORLD,&sreq);
		MPI_Wait(&sreq,&stat2);

		MPI_Get_count(&stat1,MPI_INTEGER,&count);

		printf("Rank : %d\n",rank);
		printf("Data Count: %d\n",count);
		printf("Source : %d\n",stat1.MPI_SOURCE);
		printf("TAG    : %d\n",stat1.MPI_TAG);

		free(sendbuf);
		free(recvbuf);
	}
	MPI_Finalize();

	return 0;
}
