#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 100000000

int main( int argc, char* argv[] )
{
	int rank, numtasks, count;

	int* sendbuf;
	int* recvbuf;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	MPI_Request req;
	MPI_Status stat;

	if( rank == 0 )
	{
		sendbuf = (int*)malloc(SIZE*sizeof(int));
		recvbuf = (int*)malloc(SIZE*sizeof(int));

		MPI_Irecv(recvbuf,SIZE,MPI_INTEGER,1,1313,MPI_COMM_WORLD,&req);
		/* if this recv is standard MPI_Recv, in this case
		 * the size of buffer is huge enough that may cause
		 * Dead Lock */
		/* MPI_Irecv() returned instantly and process moves into the next line */
		MPI_Send(sendbuf,SIZE,MPI_INTEGER,1,1212,MPI_COMM_WORLD);

		MPI_Wait(&req,&stat);
		/* Here, the process is halted untill the recv is over.
		 * By the req MPI_Handle, it tells that this Wait function is
		 * coresspoding to the MPI_Irecv above */
		
		MPI_Get_count(&stat,MPI_INTEGER,&count);
		printf("Rank : %d\n",rank);
		printf("Data Count: %d\n",count);
		printf("Source : %d\n",stat.MPI_SOURCE);
		printf("TAG    : %d\n",stat.MPI_TAG);


		free(sendbuf);
		free(recvbuf);
	}
	else if( rank == 1 )
	{
		sendbuf = (int*)malloc(SIZE*sizeof(int));
		recvbuf = (int*)malloc(SIZE*sizeof(int));

		MPI_Irecv(recvbuf,SIZE,MPI_INTEGER,0,1212,MPI_COMM_WORLD,&req);
		MPI_Send(sendbuf,SIZE,MPI_INTEGER,0,1313,MPI_COMM_WORLD);

		MPI_Wait(&req,&stat);
		MPI_Get_count(&stat,MPI_INTEGER,&count);
		printf("Rank : %d\n",rank);
		printf("Data Count: %d\n",count);
		printf("Source : %d\n",stat.MPI_SOURCE);
		printf("TAG    : %d\n",stat.MPI_TAG);

		free(sendbuf);
		free(recvbuf);
	}

	MPI_Finalize();

	return 0;
}
