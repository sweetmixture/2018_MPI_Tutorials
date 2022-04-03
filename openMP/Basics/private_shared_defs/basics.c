#include <stdio.h>
#include <omp.h>

int main()
{
	int a = 123;

	printf("\n\n 1> using nothing\n");
	#pragma omp parallel num_threads(2)
	{
		#pragma omp critical
		a += 10;	// would occur twice?

		printf("%d \t thread: %d\n",a,omp_get_thread_num());
	}
	printf("After omp parallel\n");
	printf("%d \t thread: %d\n",a,omp_get_thread_num());


	// private ... value should be reinit (copy base)
	printf("\n\n 2> using private\n");
	#pragma omp parallel private(a) num_threads(2)
	{
		a = 111 + omp_get_thread_num();	// a is copied value ... prbly in each stack of threads ... after the region, modification is not preserved
		printf("%d \t thread: %d\n",a,omp_get_thread_num());
	}
	printf("After omp parallel\n");
	printf("%d \t thread: %d\n",a,omp_get_thread_num());



	// firstprivate ... value preserved (copy base)
	printf("\n\n 3> using firstprivate\n");
	#pragma omp parallel firstprivate(a) num_threads(2)
	{
		a += omp_get_thread_num();	// a is copied value ... prbly in each stack of threads ... after the region, modification is not preserved
		printf("%d \t thread: %d\n",a++,omp_get_thread_num());
	}
	printf("After omp parallel\n");
	printf("%d \t thread: %d\n",a,omp_get_thread_num());


	// shared ... value preserved (copy base)
	printf("\n\n 4> using shared\n");
	#pragma omp parallel shared(a) num_threads(2)
	{
		a += (omp_get_thread_num()+1)*2;	// a is copied value ... prbly in each stack of threads ... after the region, modification is not preserved
		printf("%d \t thread: %d\n",a,omp_get_thread_num());
	}
	printf("After omp parallel\n");
	printf("%d \t thread: %d\n",a,omp_get_thread_num());
	return 0;
}


// private use // shared use // must be distinguished

/* Possible output

 1> using nothing
133 	 thread: 0
143 	 thread: 1
After omp parallel
143 	 thread: 0


 2> using private
112 	 thread: 1
111 	 thread: 0
After omp parallel
143 	 thread: 0


 3> using firstprivate
144 	 thread: 1
143 	 thread: 0
After omp parallel
143 	 thread: 0


 4> using shared
147 	 thread: 1
149 	 thread: 0
After omp parallel
149 	 thread: 0

*/
