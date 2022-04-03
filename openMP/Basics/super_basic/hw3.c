#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);

int main(int argc, char* argv[])
{
	int thread_cnt = strtol(argv[1],NULL,10);

	int rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	printf("Before Fork From thread %d of %d\n",rank,thread_count);	// at this point ... only 1 thread (Master) exists
	printf("\n");

///	///	Parallel Block Start

	#pragma omp parallel num_threads(thread_cnt)		// Thread Fork!	
	Hello();						// Implicit Barrier ... idling untill all threads joined
								// Thread Join
///	///	Parallel Block	End

	rank = omp_get_thread_num();	// 0
	thread_count = omp_get_num_threads(); // 1 expected (after threads joined)
	printf("\n");
	printf("AfterJoin From thread %d of %d\n",rank,thread_count);	// at this point ... only 1 thread (Master) exists
	printf("\n");

	return 0;
}

void Hello(void)
{
	int rank = omp_get_thread_num();
	int thread_cnt = omp_get_num_threads();
	printf("From thread %d of %d\n",rank,thread_cnt);
	return;
}
