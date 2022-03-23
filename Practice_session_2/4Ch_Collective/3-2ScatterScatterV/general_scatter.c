#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
	const int size = 10;
	int data[size];
	for(int i=0;i<size;i++)
	{	data[i] = i+1;	}

	int rank,comm_sz;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);


// SCATTER HANDLER

	int local_size = size/comm_sz;	// Assuming residue exists
	int residue    = size%comm_sz;	// 

	int sendcnt[comm_sz];		// scatterv parameter
	for(int i=0;i<comm_sz;i++) { sendcnt[i] = local_size; }
	for(int i=0;i<residue;i++) { sendcnt[i] += 1; }		// sendcnt -> block distributed ...	or "sendcnt[rank]" : send_count		_SHARED *

	int recv[ sendcnt[rank] ];	// based on the sendcnt ... set recv buffer size for each processor (differ by cores or processors)	_INDEPENDENT *

	// displs (or stride calculation)
	int displs[comm_sz];
	displs[0] = 0;
	for(int i=1;i<comm_sz;i++)
	{	displs[i] = displs[i-1] + sendcnt[i-1];	}										//	_SHARED *
	// e.g., sendcount	4 / 3 / 3
	// displs		0 / 4 / 7	... starting point !
	//			(*0,1,2,3) / (*4,5,6) / (*7,8,9)

// SCATTER HANDLER END	... possible succint version?

	// Scatter
	MPI_Scatterv(data,sendcnt,displs /* int displs[] */,MPI_INTEGER,recv,sendcnt[rank],MPI_INTEGER,0,MPI_COMM_WORLD);
	//MPI_Scatter(data,local_size,MPI_INTEGER,recv,local_size,MPI_INTEGER,0,MPI_COMM_WORLD);

	for(int i=0;i<comm_sz;i++)
	{
		if( i == rank )
		{
			printf(" Rank - %d\n",rank);
			for(int j=0;j<sendcnt[i];j++)
			{	printf("%d\t",recv[j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}

/* Possible Output

(p37) uccawkj@turing:~/mpi$ mpirun -np 3 ./a.out 
 Rank - 0
1	2	3	4	
 Rank - 1
5	6	7	
 Rank - 2
8	9	10	



(p37) uccawkj@turing:~/mpi$ mpirun -np 4 ./a.out 
 Rank - 0
1	2	3	
 Rank - 1
4	5	6	
 Rank - 2
7	8	
 Rank - 3
9	10

*/


/* : https://www.mpich.org/static/docs/v3.1/www3/MPI_Scatterv.html

int MPI_Scatterv(const void *sendbuf, const int *sendcounts, const int *displs,
                 MPI_Datatype sendtype, void *recvbuf, int recvcount,
                 MPI_Datatype recvtype,
                 int root, MPI_Comm comm)
sendbuf
address of send buffer (choice, significant only at root)
sendcounts
integer array (of length group size) specifying the number of elements to send to each processor
displs
integer array (of length group size). Entry i specifies the displacement (relative to sendbuf from which to take the outgoing data to process i
sendtype
data type of send buffer elements (handle)
recvcount
number of elements in receive buffer (integer)
recvtype
data type of receive buffer elements (handle)
root
rank of sending process (integer)
comm
communicator (handle)

*/
