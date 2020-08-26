#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define BSIZE 10

int main( int argc, char* argv[] )
{
	int rank, numtasks;
	int* data;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_rank(MPI_COMM_WORLD,&numtasks);

	if( rank == 0 )
	{
		data = (int*)malloc(BSIZE*sizeof(int));
		for(int i=0;i<BSIZE;i++)
			data[i] = i + 1;
	}
	else
		data =(int*)calloc(BSIZE,sizeof(int));

	/* MPI_Bcast() must be called for every process */
	MPI_Bcast(data,BSIZE,MPI_INTEGER,0,MPI_COMM_WORLD);


	if( rank == 1 )
	{
		for(int i=0;i<BSIZE;i++)
			printf("rank %d\t%d\n",rank,data[i]);
	}

	free(data);

	/* MPI_Bcast() copies the data into the memory in the different process
	 * 
	 * For this reason, if memory allocation is involved, users need to be more careful */

	MPI_Finalize();
	return 0;
}
