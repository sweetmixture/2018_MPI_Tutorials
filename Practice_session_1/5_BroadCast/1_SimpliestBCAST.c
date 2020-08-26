/* MPI Broad Cast */
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define BUFSIZE 10

int main ( int argc, char* argv[] )
{
	int rank, numtasks;
	int mbuf[BUFSIZE];
	int* v_in;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	if( rank == 0 ) // Master Node
	{
		v_in = (int*)malloc(BUFSIZE*sizeof(int));
		for(int i=0;i<BUFSIZE;i++)
		{	v_in[i] = i+1;
			mbuf[i] = v_in[i];	}
	}
	else
	{
		v_in = (int*)malloc(BUFSIZE*sizeof(int));

	}

	/* Bcast must be called for every processes */
	MPI_Bcast(mbuf,BUFSIZE,MPI_INTEGER,0,MPI_COMM_WORLD);


	if( rank == 0 )
	{

		free(v_in);
	}
	else if( rank == 1 )
	{
		for(int i=0;i<BUFSIZE;i++)
			printf("mbuf[%d]: %d\n",i,mbuf[i]);

		free(v_in);
	}



	MPI_Finalize();
	return 0;
}
