#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

#define SIZE 500000

int main(int argc, char* argv[])
{
	const int thc = strtol(argv[1],NULL,10);
	double et;
	int* data = (int*)malloc(SIZE*sizeof(int));

	srand((unsigned)time(NULL));


	et = -omp_get_wtime();
	#pragma omp parallel for num_threads(thc)
	for(int k=0;k<SIZE;k++)
	{	data[k] = rand()%SIZE;
	}
	et += omp_get_wtime();
	printf("OMP(t) : %d / Filling wtime(s): %lf\n",thc,et);
	printf("\n\n");


	int tmp,phase,i;
	// OddEven

	et = -omp_get_wtime();
	#pragma omp parallel num_threads(thc) private(tmp,phase,i)	// try to specify variable scopes (explicit)
	for(phase=0;phase<SIZE;phase++)
	{
		if( phase%2 == 0 )
		{
			#pragma omp for
			for(i=1;i<SIZE;i+=2)
			{
				if( data[i-1] > data[i] )
				{
					tmp = data[i];
					data[i] = data[i-1];
					data[i-1] = tmp;
				}
			}
		}
		else // odd
		{	
			# pragma omp for
			for(i=1;i<SIZE-1;i+=2)
			{
				if( data[i] > data[i+1] )
				{
					tmp = data[i+1];
					data[i+1] = data[i];
					data[i] = tmp;
				}
			}
		}
	}

	printf("sample few\n");
	for(int i=1;i<SIZE;i++)
	{	
		if( data[i-1] > data[i] )
		{	printf("Err\n"); break;	}
		else
			printf("%d\n",data[i]);
	}

	et += omp_get_wtime();
	printf("OMP(t) : %d / Filling wtime(s): %lf\n",thc,et);
	printf("\n\n");

	free(data);
	return 0;
}
