#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <omp.h>

#define LEN 20

int main(int argc,char* argv[])
{
	clock_t start,end;
	double elapsed_time;

	int thread_count, rank;
	thread_count = strtol(argv[1],NULL,10);

	int* data = (int*)calloc(LEN,sizeof(int));

	start = clock();
	
	# pragma omp parallel num_threads(thread_count)		// create parallel block
	{	
		# pragma omp for 				// omp for
		for(int i=0;i<LEN;i++)
		{	data[i] = i + 1;
			printf("Thread : %d data[%d]: %d\n",omp_get_thread_num(),i,data[i]);
		}
	}

	end = clock();
	elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;	// even gets slower
	printf("Elapsed Time 1 : %lf\n",elapsed_time);


	free(data);
	return 0;
}

/*
#include <time.h>
     
     clock_t start, end;
     double cpu_time_used;
     
     start = clock();
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
*/
