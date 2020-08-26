#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>

#define NODE1_BUF 100
#define NODE2_BUF 50

int main( int argc, char* argv[] )
{	
	srand((unsigned)time(NULL));

	int rank, numtasks;
	int count;
	clock_t srt, end;
	double time_m;
	
	double* rank_1 = NULL;
	double* rank_2 = NULL;
	
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	if( rank == 1 )
	{	srt = clock();
		/// MPI SECTION NODE # 1 ///

		rank_2 = (double*)calloc(NODE2_BUF,sizeof(double));
		
		for(int i=0;i<NODE2_BUF;i++)
			rank_2[i] = (double)(rand()%30);

		MPI_Send(&rank_2[4],NODE2_BUF-5,MPI_DOUBLE,0,1313,MPI_COMM_WORLD);	
		// the argument next to the initial buffer address indicates trasferring number of data blocks


		/// NODE # 1 Parallel END ///
		end = clock();
		time_m = (double)(srt-end)/CLOCKS_PER_SEC;

		for(int i=0;i<NODE2_BUF;i++)
			printf("NODE[%d] Buffer [%d] :  %lf\n", rank+1,i+1,rank_2[i]);

		free(rank_2);
	}
	else
	{	srt = clock();
		/// MPI SECTION NODE # 0 ///

		rank_1 = (double*)calloc(NODE1_BUF,sizeof(double));	

		for(int i=0;i<NODE1_BUF;i++)
			rank_1[i] = (double)rand()/RAND_MAX;

		MPI_Recv(&rank_1[5], NODE1_BUF ,MPI_DOUBLE,1,1313, MPI_COMM_WORLD,&status);
	//	MPI_Recv(&rank_1[NODE1_BUF], NODE2_BUF ,MPI_DOUBLE,1,1313, MPI_COMM_WORLD,&status);	
		/* Data will be reported in the following heap memory; not accessible */

		printf("Destination: %d received data from processor %d \n",rank,status.MPI_SOURCE);
		MPI_Get_count(&status,MPI_DOUBLE,&count);
		printf("Destination: %d Got %d elements \n",rank,count);
		/// NODE # 0 Parallel END ///
		end = clock();
		time_m = (double)(srt-end)/CLOCKS_PER_SEC;	

		for(int i=0;i<NODE1_BUF;i++)
			printf("NODE[%d] Buffer [%d] :  %lf\n", rank+1,i+1,rank_1[i]);

		
		free(rank_1);
	}
	MPI_Finalize();

	return 0;
}
