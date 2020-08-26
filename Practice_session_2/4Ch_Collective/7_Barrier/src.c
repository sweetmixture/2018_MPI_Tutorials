#include<stdio.h>
#include<mpi.h>


int main( int argc, char* argv[] )
{
    const int MPI_Root = 0;
    int numtasks,rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);


    if( rank == numtasks-1 )
    {
        for(int i=0;i<100000000;i++);
    }

    //MPI_Barrier(MPI_COMM_WORLD);      // For Calc Sync

    // Do test for both cases, with and without MPI_Barrier

    for(int i=0;i<numtasks;i++)
    {
        if( i == rank )
            printf("I am rank: %d\n",rank);
    }


    MPI_Finalize();

    return 0;
}
