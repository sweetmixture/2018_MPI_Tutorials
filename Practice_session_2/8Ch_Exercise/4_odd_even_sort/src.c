#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include<mpi.h>

#define LEN_ 100000000
#define MAX_ 100000000

void OddEvenSort( int* arr, const int cnt );	// in/out // in

int main()
{
	srand(time(NULL));
	
	double time_start, time_end;
	int rank, comm_sz;

	int* tmp = (int*)calloc(LEN_,sizeof(int));
	int* data = (int*)calloc(LEN_,sizeof(int));

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

	// cyc dis
	int cyc_dis_idx = 0;

	time_start = MPI_Wtime();
	for(int i=rank;i<LEN_;i=rank+cyc_dis_idx*comm_sz)
	{	tmp[i] = rand()%MAX_;
		cyc_dis_idx++;
	}
	time_end = MPI_Wtime();

	MPI_Allreduce(tmp,data,LEN_,MPI_INTEGER,MPI_SUM,MPI_COMM_WORLD);

	//if(rank==0) { printf("list gen time : %.4lf\n",time_end-time_start); }
	//if(rank == 0 ) { for(int i=0;i<LEN_;i++) { printf("%d\n", tmp[i]); } }
	//if(rank == 0 ) { for(int i=0;i<LEN_;i++) { printf("%d\n", data[i]); } }

	
	free(data);
	free(tmp);
	MPI_Finalize();
	return 0;
}

void OddEvenSort( int* arr, const int cnt )
{



	return;
}


void OddEvenSort( int* arr, const int cnt )
{
	int phase, i, temp;

	for(phase=0;phase<cnt;phase++)
	{	if(phase%2 == 0)		// Even
		{	for(i=1;i<cnt;i+=2)
			{
				if(arr[i-1]>arr[i])
				{	temp = arr[i];
					arr[i]   = arr[i-1];
					arr[i-1] = temp;
				}
			}
		}
		else				// Odd
		{	for(i=1;i<cnt-1;i+=2)
			{
				if(arr[i]>arr[i+1])
				{	temp = arr[i];
					arr[i]   = arr[i+1];
					arr[i+1] = temp;
				}
			}
		}
	}
	return;
}			





