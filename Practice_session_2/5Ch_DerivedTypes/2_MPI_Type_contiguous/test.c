#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int numtasks,rank;
    const int MPI_Root = 0;
    int buf[15];

    MPI_Datatype newtype;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if( rank == MPI_Root )
        for(int i=0;i<15;i++) buf[i] = i+1;
    else
        memset(buf,0,15*sizeof(int));

    MPI_Type_contiguous(3,MPI_INT,&newtype);
    MPI_Type_commit(&newtype);

    MPI_Bcast(buf,3,newtype,0,MPI_COMM_WORLD);
    if( rank == 1 )
        for(int i=0;i<15;i++)   printf("%d\n",buf[i]);

    MPI_Type_free(&newtype);

    MPI_Finalize();
    return 0;
}
