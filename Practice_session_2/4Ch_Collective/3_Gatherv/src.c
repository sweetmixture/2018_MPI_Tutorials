#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_blas.h>
#include<mpi.h>


/*
   MPI_Gatherv( void* sendbuf, int sendcount, MPI_Datatpe sendtype, void* recvbuf, int* rcnt, int* displs, MPI_Datatype recvtype, int root, MPI_Comm comm )
*/




int main( int argc, char* argv[] )
{
    const int MPI_Root = 0;
    int numtasks, rank;

    int* MPI_Send_ws;
    int* MPI_Recv_ws;

    int rcnt[3]={1,2,3}; 
    int displs[3]={0,1,3};
    int scnt;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    MPI_Send_ws = (int*)calloc(3,sizeof(int));
    MPI_Recv_ws = (int*)calloc(6,sizeof(int));

    for(int i=0;i<rank+1;i++)
        MPI_Send_ws[i] = i+rank+1;

    scnt = rank+1;

    MPI_Gatherv(MPI_Send_ws,scnt,MPI_INTEGER,MPI_Recv_ws,rcnt,displs,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);

    if( rank == MPI_Root )
    {
        printf("ROOT GATHERV DONE\n");
        
        for(int i=0;i<6;i++)
            printf("%d\n",MPI_Recv_ws[i]);
    }
    

    free(MPI_Recv_ws);
    free(MPI_Send_ws);

    MPI_Finalize();

    return 0;
}
