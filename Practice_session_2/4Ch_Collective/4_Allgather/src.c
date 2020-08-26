#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main( int argc, char* argv[] )
{
    const int MPI_Root = 0;
    int numtasks, rank;

    int* Recv;
    int* Send;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    Send = (int*)calloc(3,sizeof(int));
    Recv = (int*)calloc(3*numtasks,sizeof(int));
    
    for(int i=0;i<3;i++)
        Send[i] = rank+1;

    MPI_Allgather(&Send[0],3,MPI_INTEGER,&Recv[0],3,MPI_INTEGER,MPI_COMM_WORLD);

    for(int i=0;i<numtasks;i++)
    {
        if( i == rank )
        {
            printf("in rank: %d, recv data set\n", rank);
            for(int i=0;i<3*numtasks;i++)
                printf("%d\n",Recv[i]);
        }
    }
    
    free(Send);
    free(Recv);

    MPI_Finalize();
    return 0;
}
