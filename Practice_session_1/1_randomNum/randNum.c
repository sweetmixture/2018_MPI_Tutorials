#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>

int main( int argc, char* argv[] )
{
	srand((unsigned)time(NULL));

	int rank;
	int numtasks;

	double drand;
	int intrand;
	
	clock_t start, end;
	double res;


	start = clock();

	for(int i=0;i<1000000000;i++)
	{	drand = (double)rand()/RAND_MAX;
	//	printf("rank:\t%d\trand:\t%lf\n",rank,drand);	
	}
	for(int i=0;i<1000000000;i++)
	{	intrand = rand()%100;
	//	printf("rank:\t%d\trand:\t%d\n",rank,intrand);	
	}


	end = clock();

	res = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Performance: %lf\n",res);

	return 0;
}

/* Takes ~ 14 sec */
