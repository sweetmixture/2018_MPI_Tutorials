#include<string.h>
#include<stdio.h>
#include<gsl/gsl_vector.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
	int rank, numtasks;
	const int root = 0;

	gsl_vector* v = NULL;
	double recv[2];	memset(recv,0,sizeof(double)*2);

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

	v = gsl_vector_calloc(2);

	if(rank==root)
		gsl_vector_set(v,0,1);
	else
		gsl_vector_set(v,1,2);

	
	MPI_Gather(&v->data[0+rank],1,MPI_DOUBLE,recv,1,MPI_DOUBLE,root,MPI_COMM_WORLD);
	// Parametrically one can choose the send data address
	// In this case, by using variable 'rank' sending individual elem of vector 'v' into 'recv' array

	if(rank==root)
		for(int i=0;i<2;i++)	printf("%lf\t",recv[i]);
	puts("");





	gsl_vector_free(v);

	MPI_Finalize();

	return 0;
}
