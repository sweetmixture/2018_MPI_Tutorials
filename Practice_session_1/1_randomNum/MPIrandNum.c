#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>

int main( int argc, char* argv[] )
{
	srand((unsigned)time(NULL));
	
	clock_t start1, end1, start2, end2;
	clock_t start3, end3, start4, end4;
	double res1, res2, res3, res4;

	int rank;
	int numtasks;

	double drand;	
	int intrand;
//	int index = 1;
	
	// SetUp MPI ENVIRONMENT
	MPI_Init(&argc, &argv);
	
	printf("Pass\n");	// for this case, the argument called in both processes

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);	

//	index ++;
	printf("pass (Process) rank: %d\n",rank);


	if( rank == 0 )
	{	start1 = clock();
		for(int i=0;i<1000000000;i++)
		{	drand = (double)rand()/RAND_MAX;
		//	printf("rank:\t%d\trand:\t%lf\n",rank,drand);
		}
		end1 = clock();
		res1 = (double)(end1-start1)/CLOCKS_PER_SEC;
		printf("Performance: %lf\t Rank: %d\n",res1,rank);
		printf("process size:\t%d\n",numtasks);
	}
	else if( rank == 1 )
	{	start2 = clock();
		for(int i=0;i<1000000000;i++)
		{	intrand = rand()%100;
		//	printf("rank:\t%d\trand:\t%d\n",rank,intrand);
		}
		end2 = clock();
		res2 = (double)(end2-start2)/CLOCKS_PER_SEC;
		printf("Performance: %lf\t Rank: %d\n",res2,rank);
		printf("process size:\t%d\n",numtasks);
	}
	else if( rank == 2 )
	{	start3 = clock();
		for(int i=0;i<1000000000;i++)
		{	intrand = rand()%100;
		//	printf("rank:\t%d\trand:\t%d\n",rank,intrand);
		}
		end3 = clock();
		res3 = (double)(end3-start3)/CLOCKS_PER_SEC;
		printf("Performance: %lf\t Rank: %d\n",res3,rank);
		printf("process size:\t%d\n",numtasks);
	}
	else
	{	start4 = clock();
		for(int i=0;i<1000000000;i++)
		{	intrand = rand()%100;
		//	printf("rank:\t%d\trand:\t%d\n",rank,intrand);
		}
		end4 = clock();
		res4 = (double)(end4-start4)/CLOCKS_PER_SEC;
		printf("Performance: %lf\t Rank: %d\n",res4,rank);
		printf("process size:\t%d\n",numtasks);
	}

	MPI_Finalize();
	// END MPI

	return 0;
}	

/* Takes around ~ 7 sec */
