#include<stdio.h>
#include<mpi.h>
#include<string.h>
#include<stdlib.h>

int main( int argc, char* argv[] )
{
	int rank, numtasks;
	const int root = 0;

	int send[10];
	int recv[10];	memset(recv,0,sizeof(int)*10);

	int rcnt[4];	for(int i=0;i<4;i++)	rcnt[i] = i+1;
	int displs[4];
	
	int scnt;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	for(int i=0;i<10;i++)
		send[i] = i+1;
	
	displs[0]=0; displs[1]=1; // displs[2] = 3; // displs[3] = 6; // ..
	for(int i=2;i<4;i++)
		displs[i] = displs[i-1]-displs[i-2]+displs[i-1]+1;

	scnt = rank + 1;

	MPI_Gatherv(&send[displs[rank]],scnt,MPI_INTEGER,
			&recv[0],&rcnt[0],&displs[0],MPI_INTEGER,root,MPI_COMM_WORLD);

	//MPI_Bcast

	if( rank == root )
	{	for(int i=0;i<10;i++)
		{	printf("rank: %d\t recv[%d]: %d\n",
					rank, i, recv[i]);
		}
	}

	MPI_Finalize();

	return 0;
}
