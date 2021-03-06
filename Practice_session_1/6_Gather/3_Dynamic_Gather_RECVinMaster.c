/* MPI_Gather() with dynamic alloc */

/* Recv buffer for MPI_Gather() is only necessary 
 * for the node which is used as the root */
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 10

int main (int argc,char*argv[])
{
	int rank, tasknum;
	
	const int master = 0;
	
	int* data;
	int* recv;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&tasknum);

	data = (int*)malloc(SIZE*sizeof(int));
	/* SIZE: sizeof buffer
	 * tasknum: number of nodes in use
	 */
	
	if( rank == 0 )
	{
		for(int i=0;i<SIZE;i++)
			data[i] = i+1;
		recv = (int*)calloc(SIZE*tasknum,sizeof(int));	
	}	/* Here, recv buffer is only dynamically allocated in master node */
	else
	{
		for(int i=0;i<SIZE;i++)
			data[i] = SIZE+i+1;
	}
	
	MPI_Gather(data,SIZE,MPI_INTEGER,
			recv,SIZE,MPI_INTEGER, master,MPI_COMM_WORLD);
	/* Recv count must be equal with the number of data
	 * recv in each node, NOT the total # of elements */
	/* recv is only done on master node ! */
	if( rank == master )
	{
		for(int i=0;i<SIZE*tasknum;i++)
			printf("%d\n",recv[i]);

		free(recv);
	}




	free(data);
	MPI_Finalize();

	return 0;
}
