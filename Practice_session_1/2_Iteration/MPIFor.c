#include<stdio.h>
#include<mpi.h>
#include<time.h>

int main( int argc, char* argv[] )
{
	int rank;
	int numtasks;
	int data;	// if the variable gets into MPI environment, it acts as independent variables in each core(or Node)

	int result1, result2, totalresult;

	clock_t start, end;
	double res;
	

	printf("MPI before init\n");	/* This will be printed out twice...
       					   Proves that main function executes in both core 
					   However, this is not in 'MPI_Init()', this is not specified but undefined */

	MPI_Init(&argc,&argv);

	start = clock();

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	printf("pass\n");
	printf("pass Rank: %d\n",rank);
	
	if( rank == 0 )	 // In core-1
	{	for(int i=0;i<=10;i++)
		{	
			data += i;	// data is used as an independent variable in each core(or Node)
			printf("Num: %d\tRank: %d\n",data,rank);
		}
	}
	else		// In core-2
	{	for(int i=0;i<=5;i++)
		{	
			data += i;	// data is used as an independent variable in each core(or Node)
			printf("Num: %d\tRank: %d\n",data,rank);
		}
	}


	end = clock();
	res = (double)(end-start)/CLOCKS_PER_SEC;

	printf("Performance: %lf\t Rank: %d\n", res, rank );

	if( rank == 0 )
	{	result1 = data;
		printf("result1 : %d\t rank: %d\n",result1,rank);
	}
	else
	{	result2 = data;
		printf("result2 : %d\t rank: %d\n",result2,rank);
	}


	MPI_Finalize();

//	totalresult = result1 + result2;
//	printf("total Sum: %d\n", totalresult);
	// ERRROR 
	/* To get this total sum done, now it needs communication */

	return 0;
}
