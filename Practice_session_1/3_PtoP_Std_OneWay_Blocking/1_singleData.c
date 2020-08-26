#include<stdio.h>
#include<mpi.h>

int main( int argc, char* argv[] )
{
	int rank, numtasks, count;

	double src,dest;

	MPI_Init( &argc, &argv );
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	MPI_Status status;

	if( rank == 0 )
	{
		src = 14.32;
		printf("Source: %d hase data : %lf\n",rank,src);
		// Standard Data Send
		MPI_Send(&src,1,MPI_DOUBLE,1,12345,MPI_COMM_WORLD);
	}
	else
	{	// Standard Data Recv
		MPI_Recv(&dest,1,MPI_DOUBLE,0,12345,MPI_COMM_WORLD,&status);

		/* WILDCARD */	
		//MPI_Recv(&dest,1,MPI_DOUBLE,MPI_ANY_SOURCE,12345,MPI_COMM_WORLD,&status);
		//MPI_Recv(&dest,1,MPI_DOUBLE,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

		printf("Destination: %d received data from processor %d \n",rank,status.MPI_SOURCE);
		MPI_Get_count(&status,MPI_DOUBLE,&count);
		printf("Destination: %d Got %d elements \n",rank,count);
		printf("Destination: %d dest = %lf \n",rank, dest );
	
		printf("\nMPI_STATUS\n");
		printf("MPI_SOURCE	: %d\n",status.MPI_SOURCE);
		printf("MPI_TAG		: %d\n",status.MPI_TAG);
		printf("MPI_ERROR	: %d\n",status.MPI_ERROR);
	}

	MPI_Finalize();

	return 0;
}

/* int MPI_Get_count( MPI_Status * status, MPI_Datatype datatype, int *count );
 *
 * typedef struct _MPI_Status
 * {
 * 	int count;
 * 	int cancelled;
 * 	int MPI_SOURCE;
 * 	int MPI_TAG;
 * 	int MPI_ERROR;
 * }MPI_Status;
 *
 * RECV Wild Cards - 'int source' section can be replaced with...
 * * MPI_ANY_SOURCE
 * * MPI_ANY_TAG
 *
 * int MPI_Recv( void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status );
 * int count: this argument tells the number of data gonna be accepted ... must be larger than the data sent
 * 	// data storing starts from *buf to the end of  '&buf + count*izeof(buff)'
 *
 * int MPI_Send( void* buf, int count, MPI_Datatype datatpye, int dest  , int tag, MPI_Comm comm );
 * int count: this argument tells the number of data gonna be sent
 */


/* SEND RECV TAG MUST MATCH !
 */
