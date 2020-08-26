/* MPI_Gather() with dynamic alloc */
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SIZE 10

int main (int argc,char*argv[])
{
	int rank, size;
	
	int* data;
	int* recv;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	data = (int*)malloc(SIZE*sizeof(int));
	recv = (int*)calloc(SIZE*size,sizeof(int));
	/* SIZE: sizeof buffer
	 * size: number of nodes in use
	 */

	if( rank == 0 )
	{	for(int i=0;i<SIZE;i++)
		{	data[i] = i+1;
			printf("%d\t",data[i]);	
		}
		printf("\n");
		printf("%d\n",SIZE*size);
	}
	else
	{	for(int i=0;i<SIZE;i++)
		{	data[i] = SIZE+i+1;			
			printf("%d\t",data[i]);	
		}
		printf("\n");
	}		

	if( rank == 0 )
	{	printf("Rank: %d \t Recv buffer\n",rank);
		for(int i=0;i<SIZE*size;i++)
			printf("%d\n",recv[i]);		
	}
	
	MPI_Gather(data,SIZE,MPI_INTEGER,
			recv,SIZE,MPI_INTEGER, 0,MPI_COMM_WORLD);
	/* Gather the data in root ( rank == 0 ) */

	if( rank == 0 )
	{	printf("Rank: %d \t Recv buffer\n",rank);
		for(int i=0;i<SIZE*size;i++)
			printf("%d\n",recv[i]);		
	}

	free(recv);
	free(data);
	MPI_Finalize();

	return 0;
}
