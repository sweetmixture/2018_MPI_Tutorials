#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include<gsl/gsl_blas.h>

int main( int argc, char* argv[] )
{
    srand((unsigned)time(NULL));

    const int MPI_Root = 0;
    int numtasks, rank;

    int* MPI_Send_ws = (int*)calloc(1,sizeof(int));
    int* MPI_Recv_ws = NULL;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    MPI_Recv_ws = (int*)calloc(numtasks,sizeof(int));

    for(int i=0;i<numtasks;i++)
    {   if( i == rank )
        {   MPI_Send_ws[0] = i+1;
            printf("In rank: %d, data : %d\n",rank,MPI_Send_ws[0]);
        }
    }

    MPI_Gather(MPI_Send_ws,1,MPI_INTEGER,MPI_Recv_ws,1,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);
    if( rank == MPI_Root )    printf("Gather done\n");


    if( rank == MPI_Root )
    {
        for(int i=0;i<numtasks;i++)
            printf("%d\n",MPI_Recv_ws[i]);
    }



    free(MPI_Recv_ws);
    
    MPI_Finalize();

    free(MPI_Send_ws);

    return 0;
}
