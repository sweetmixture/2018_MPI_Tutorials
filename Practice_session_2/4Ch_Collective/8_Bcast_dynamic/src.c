#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

int main(int argc,char* argv[])
{
    int numtasks, rank;

    int* data;


    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    data = (int*)calloc(10,sizeof(int));

    if( rank == 0 )
        for(int i=0;i<10;i++)
            data[i] = i +1;

    MPI_Bcast(data,10,MPI_INTEGER,0,MPI_COMM_WORLD);

    if( rank != 0 )
        for(int i=0;i<10;i++)
            printf("%d\n",data[i]);




    free(data);
    MPI_Finalize();

    return 0;
}
