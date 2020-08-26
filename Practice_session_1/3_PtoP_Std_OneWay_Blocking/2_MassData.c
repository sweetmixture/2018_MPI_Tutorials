#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define R0_SIZE 100
#define R1_SIZE 50

int main( int argc, char* argv[] )
{
	int rank, numtasks;
	int recv_count;

	double* t_buff0;
	double* t_buff1;
	double tmp;

	MPI_Status status;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);


	if( rank == 0 )
	{
		t_buff0 = (double*)calloc(R0_SIZE,sizeof(double));
		
		for(int i=0;i<R0_SIZE;i++)
		{	t_buff0[i] = (double)i+1.;
			printf("CORE : %d\t VAL[%d]: %lf\n",rank,i+1,t_buff0[i]);
		}
		MPI_Send(&t_buff0[0],12,MPI_DOUBLE,1,1212,MPI_COMM_WORLD);
		printf("SEND -1 DONE\n");	/* SEND FROM [0] ~ [11] */
		MPI_Send(&t_buff0[50],25,MPI_DOUBLE,1,1313,MPI_COMM_WORLD);
		printf("SEND -2 DONE\n");	/* SEND FROM [49] ~ [49 + 25] */
		free(t_buff0);
	}
	else
	{
		t_buff1 = (double*)calloc(R1_SIZE,sizeof(double));


		MPI_Recv(&t_buff1[25],25,MPI_DOUBLE,0,1313,MPI_COMM_WORLD,&status);
		/* Recv saved in [24] ~ [49] */
		MPI_Get_count(&status,MPI_DOUBLE,&recv_count);
		printf("* RECV - 1 DONE \n");
		printf("\nCORE: %d Got %d elements \n",rank,recv_count);
		printf("Source		: %d\n",status.MPI_SOURCE);
		printf("MPI_TAG		: %d\n",status.MPI_TAG);
		printf("MPI_ERROR	: %d\n",status.MPI_ERROR);

		for(int i=0;i<R1_SIZE;i++)
			printf("CORE : %d\t VAL[%d]: %lf\n",rank,i+1,t_buff1[i]);

		MPI_Recv(&t_buff1[25],12,MPI_DOUBLE,0,1212,MPI_COMM_WORLD,&status);
		/* Recv saved in [24] ~ [36] */
		// This Receiving happens later, so it overwrites the previous buffer
		MPI_Get_count(&status,MPI_DOUBLE,&recv_count);
		printf("\n* RECV - 2 DONE \n");
		printf("\nCORE: %d Got %d elements \n",rank,recv_count);
		printf("Source		: %d\n",status.MPI_SOURCE);
		printf("MPI_TAG		: %d\n",status.MPI_TAG);
		printf("MPI_ERROR	: %d\n",status.MPI_ERROR);

		for(int i=0;i<R1_SIZE;i++)
			printf("CORE : %d\t VAL[%d]: %lf\n",rank,i+1,t_buff1[i]);
		

		free(t_buff1);
	}

	MPI_Finalize();
	return 0;
}
