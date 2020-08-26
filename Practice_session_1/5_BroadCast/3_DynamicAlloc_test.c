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

	/* dynamic alloc for every processes */
	data = (int*)malloc(BSIZE*sizeof(int));

	if( rank == 0 )
	{
		printf("rank %d: %x\n",rank, &data[0]);
		for(int i=0;i<BSIZE;i++)
		{	data[i] = i+1;
			printf("rank %d\t%d\n",rank,data[i]);	}
	}

	/* MPI_Bcast() for every processes */
	MPI_Bcast(data,BSIZE,MPI_INTEGER,0,MPI_COMM_WORLD);

	if( rank == 1 )
	{
		printf("rank %d: %x\n",rank, &data[0]);
		for(int i=0;i<BSIZE;i++)
			printf("rank %d\t%d\n",rank,data[i]);
	}

	free(data);
	/* Even the memory addresses in the both processes are different
	 *
	 * MPI_Bcast works still fine */

	/* MPI_Bcast() and dynamic allocation must be called for every processes
	 */

	MPI_Finalize();
	return 0;
}
