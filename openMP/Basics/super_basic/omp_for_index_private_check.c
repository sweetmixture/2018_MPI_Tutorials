#include <stdio.h>
#include <omp.h>

void main()
{
	#pragma omp prallel for num_threads(4)
	for(int i=0;i<20;i++)
	{
		printf("%d\n",i);
	}
	printf("parallel for directive - right above for loop\n");
	printf("\n\n");


	#pragma omp prallel for num_threads(4)
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("%d,%d\n",i,j);
		}
		if( omp_get_thread_num() == 0 )
		{	printf("\n");
		}
	}
	printf("parallel directive- i,j nested\n");
	printf("\n\n");
}
