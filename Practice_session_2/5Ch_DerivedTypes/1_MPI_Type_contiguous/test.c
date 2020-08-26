#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
    int numtasks, rank;
    const int MPI_Root = 0;
    int buf[20];

    MPI_Datatype inewtype;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if( rank == MPI_Root )
    {   for(int i=0;i<20;i++)
            buf[i] = i+1;
    }
    else
        memset(buf,0,20*sizeof(int));

    MPI_Type_contiguous(10,MPI_INT,&inewtype);
    MPI_Type_commit(&inewtype);

    MPI_Bcast(buf,2,inewtype,0,MPI_COMM_WORLD);

    if( rank == 1 )
    {
        printf("rank: %d\n",rank);
        for(int i=0;i<20;i++)
            printf("buf[%d] = %d\n",i,buf[i]);
    }

    MPI_Type_free(&inewtype);

    MPI_Finalize();

    return 0;
}
