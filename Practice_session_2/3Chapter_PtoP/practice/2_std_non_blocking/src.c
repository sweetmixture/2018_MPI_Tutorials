#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

#define MPI_Root 0

int main( int argc, char* argv[] )
{
    int numtasks,rank,cnt;

    int *send,*recv;

    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    send = (int*)calloc(3,sizeof(int)); recv = (int*)calloc(3,sizeof(int));
    
    if( rank == MPI_Root )
        for(int i=0;i<3;i++)
            send[i] = i + 1;

    if( rank == MPI_Root )
        MPI_Isend(send,3,MPI_INTEGER,1,123,MPI_COMM_WORLD,&request);                // send 1st src: Root


    if( rank == 1 )
        MPI_Irecv(send,3,MPI_INTEGER,MPI_Root,123,MPI_COMM_WORLD,&request);         // recv 1st dest: 1
    
    
    if( rank == MPI_Root )
    {   
        MPI_Wait(&request,&status); // make sure if the data transfered

        for(int i=0;i<3;i++)
            send[i] = send[i] + 1;                                                  // send done / make change the send buffer

        MPI_Isend(send,3,MPI_INTEGER,1,124,MPI_COMM_WORLD,&request);                // send 2nd set src: Root
        MPI_Wait(&request,&status);
    }


    if( rank == 1 )
    {
        MPI_Wait(&request,&status);                                                 // make sure 1st send recv
        
        printf("rank:%d 1st recv done\n",rank);
        for(int i=0;i<3;i++)
            printf("%d\t",send[i]);
        puts("");


        MPI_Irecv(recv,3,MPI_INTEGER,0,124,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status); // confirm the 2nd data transfer

        printf("rank:%d 2nd recv done\n",rank);
        for(int i=0;i<3;i++)
            printf("%d\t",recv[i]);
        puts("");

        // do calc when all data sent;
        for(int i=0;i<3;i++)
            send[i] = send[i]*recv[i];


        // send back to Root
        MPI_Isend(send,3,MPI_INTEGER,MPI_Root,125,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);
    }

    if( rank == MPI_Root )
    {
        MPI_Irecv(recv,3,MPI_INTEGER,1,125,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);

        printf("rank: %d\t Final\n",rank);

        for(int i=0;i<3;i++)
            printf("%d\t",recv[i]);
        puts("");
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Bcast(recv,3,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);

    if( rank == 1 )
    {
        printf("rank: %d\t Final\n",rank);

        for(int i=0;i<3;i++)
            printf("%d\t",recv[i]);
        puts("");
    }

    free(send); free(recv);

    MPI_Finalize();

    return 0;
}
