#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 10

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
		for(int i=0;i<SIZE;i++)
			sendbuf[i] = i;
		
		MPI_Irecv(recvbuf,SIZE,MPI_INTEGER,1,1212,MPI_COMM_WORLD,&rreq);
		MPI_Send(&sendbuf[4],5,MPI_INTEGER,1,1313,MPI_COMM_WORLD);
		MPI_Wait(&rreq,&stat1);
		
		MPI_Get_count(&stat1,MPI_INTEGER,&count);

		printf("Rank : %d\n",rank);
		printf("Data Count: %d\n",count);
		printf("Source : %d\n",stat1.MPI_SOURCE);
		printf("TAG    : %d\n",stat1.MPI_TAG);
		for(int i=0;i<SIZE;i++)
			printf("%d\n",recvbuf[i]);
		printf("\n");

		free(sendbuf);
		free(recvbuf);
	}
	else
	{
		sendbuf = (int*)calloc(SIZE,sizeof(int));
		recvbuf = (int*)calloc(SIZE,sizeof(int));
		
		for(int i=0;i<SIZE;i++)
			sendbuf[i] = i+13; 

		MPI_Irecv(recvbuf,SIZE,MPI_INTEGER,0,1313,MPI_COMM_WORLD,&rreq);
		MPI_Send(sendbuf,SIZE,MPI_INTEGER,0,1212,MPI_COMM_WORLD);
		MPI_Wait(&rreq,&stat1);

		MPI_Get_count(&stat1,MPI_INTEGER,&count);

		printf("Rank : %d\n",rank);
		printf("Data Count: %d\n",count);
		printf("Source : %d\n",stat1.MPI_SOURCE);
		printf("TAG    : %d\n",stat1.MPI_TAG);
		for(int i=0;i<SIZE;i++)
			printf("%d\n",recvbuf[i]);
		printf("\n");

		free(sendbuf);
		free(recvbuf);
	}
	MPI_Finalize();

	return 0;
}
