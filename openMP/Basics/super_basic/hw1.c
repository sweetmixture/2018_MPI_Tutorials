#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
	#pragma omp parallel
	printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());

	return 0;
}

// which gcc-10 / gcc-10 -fopenmp
