#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main( int argc, char* argv[] )
{
    const int MPI_Root = 0;
    int numtasks, rank;

    int Send[2];
    int Recv[2];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    for(int i=0;i<2;i++)
        Send[i] = (rank*2)+i+1;
    
    for(int i=0;i<numtasks;i++)
    {
        if( i == rank )
        {
            printf("Rank:%d\n",rank);
            for(int j=0;j<2;j++)
                printf("%d\n",Send[j]);
        }
    }



    MPI_Reduce(&Send[0],&Recv[0],2,MPI_INTEGER,MPI_SUM,MPI_Root,MPI_COMM_WORLD);
    if( rank == MPI_Root )
    {   
        printf("Reduce, done\n");

        for(int i=0;i<2;i++)
            printf("%d\n",Recv[i]);
    }

    MPI_Finalize();

    return 0;
}
