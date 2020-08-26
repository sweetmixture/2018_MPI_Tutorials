#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

int main(int argc,char* argv[])
{
    const int MPI_Root = 0;
    int numtasks,rank;
    int buf[20];

    MPI_Datatype newtype;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    //MPI_Type_hvector(6,2,3*sizeof(int),MPI_INTEGER,&newtype);
    MPI_Type_vector(6,2,3,MPI_INTEGER,&newtype);
    MPI_Type_commit(&newtype);

    if( rank == MPI_Root )
        for(int i=0;i<20;i++) buf[i] = i+1;
    else
        memset(buf,0,20*sizeof(int));

    MPI_Bcast(buf,1,newtype,0,MPI_COMM_WORLD);
    
    if( rank == 1 )
        for(int i=0;i<20;i++) printf("%d\n",buf[i]);

    MPI_Type_free(&newtype);

    MPI_Finalize();
    return 0;
}
