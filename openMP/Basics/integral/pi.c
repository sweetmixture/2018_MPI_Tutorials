#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
#include <omp.h>

int main(int argc, char* argv[])
{
	const int thc = strtol(argv[1],NULL,10);

	const int k_max = 2000000000;

	double factor;
	double res = 0.;
	double elapsed_time;

	elapsed_time = -omp_get_wtime();

	#pragma omp parallel num_threads(thc) shared(res) private(factor)
	{	
		#pragma omp for reduction(+:res)
		for(int k=0;k<k_max;k++)
		{	
			factor = (k%2==0)?1.:-1.;
			res += 4.*factor/(2.*k+1);		// k 'local' stack on each thread 	// previous 'pow()' 2 times slower
		}						// res -> shared 
	}

	elapsed_time += omp_get_wtime();
	printf("calculated pi : %.12f\n",res);
	printf("wtime : %lf (s)\n",elapsed_time);
	
	return 0;
}
