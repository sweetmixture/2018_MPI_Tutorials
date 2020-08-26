/* Simple MPI_Gather() */
#include<stdio.h>
#include<mpi.h>

int main( int argc, char* argv[] )
{
	int rank, numtasks;
	
	int data;
	int recv[2];

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	data = rank + 1;
	// save 0 -> Mater node(0)
	// save 1 -> node(1)
	
	
	/* MPI_Gather
	 *
	 * Node 2 -> Node 1
	 * Into the Recv Buffer
	 *
	 * Here, Recv buff is seperated with
	 * the Send buff, which is must be divided
	 *
	 * also, the size of gathered data must be same */	
	MPI_Gather(&data,1,MPI_INTEGER,
			&recv[0],1,MPI_INTEGER, 0,MPI_COMM_WORLD);

	if( rank == 0 )
	{	
		printf("rank %d\n",rank);
		for(int i=0;i<2;i++)
			printf("%d\n",recv[i]);
	}
	else
	{
		printf("rank %d\n",rank);
		for(int i=0;i<2;i++)
			printf("%d\n",recv[i]);
	}


	MPI_Finalize();
	return 0;
}
