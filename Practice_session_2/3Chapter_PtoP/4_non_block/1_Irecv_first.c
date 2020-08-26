#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

int main( int argc, char* argv[] )
{
    const int root = 0;
    int numtasks, rank;
    
    double* MPI_RECV_B = (double*)malloc(10*sizeof(double));
    double* MPI_SEND_B = (double*)malloc(10*sizeof(double));


    MPI_Request request; MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if( rank == root )
    {   for(int i=0;i<10;i++)
            MPI_SEND_B[i] = 2*(i+1);   
    }
    else
    {   for(int i=0;i<10;i++)
            MPI_SEND_B[i] = 2*(i+1)-1;
    }

    if( rank == root )
    {
        MPI_Irecv(&MPI_RECV_B[0],10,MPI_DOUBLE,1,13,MPI_COMM_WORLD,&request);

        MPI_Send(&MPI_SEND_B[0],10,MPI_DOUBLE,1,14,MPI_COMM_WORLD);
        printf("MPI_SEND src %d -> dest 1, done\n",rank);

        MPI_Wait(&request,&status);
        printf("MPI_IRECV src %d -> dest %d, done\n",status.MPI_SOURCE,rank);
        for(int i=0;i<10;i++)
            printf("%lf - node: %d\n",MPI_RECV_B[i],rank);
    }
    
    if( rank == 1 )
    {
        MPI_Irecv(&MPI_RECV_B[0],10,MPI_DOUBLE,root,14,MPI_COMM_WORLD,&request);

        MPI_Send(&MPI_SEND_B[0],10,MPI_DOUBLE,root,13,MPI_COMM_WORLD);
        printf("MPI_SEND src %d -> dest 0, done\n",rank);

        MPI_Wait(&request,&status);
        printf("MPI_IRECV src %d -> dest %d, done\n",status.MPI_SOURCE,rank);
        for(int i=0;i<10;i++)
            printf("%lf - node: %d\n",MPI_RECV_B[i],rank);
    }


    MPI_Finalize();


    free(MPI_RECV_B);
    free(MPI_SEND_B);

    return 0;
}
