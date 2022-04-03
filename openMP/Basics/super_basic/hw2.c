#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);

int main(int argc, char* argv[])
{
	int thread_cnt = strtol(argv[1],NULL,10);

	#pragma omp parallel num_threads(thread_cnt)
	Hello();

	return 0;
}

void Hello(void)
{
	int rank = omp_get_thread_num();
	int thread_cnt = omp_get_num_threads();

	printf("From thread %d of %d\n",rank,thread_cnt);
	return;
}
