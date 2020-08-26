#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

#define MPI_Root 0

int main(int argc,char*argv[])
{
    int rank,numtasks,cnt;
    
    int *send, *recv;

    MPI_Status status;

    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    send = (int*)calloc(3,sizeof(int));
    recv = (int*)calloc(3,sizeof(int));
    
    if( rank == MPI_Root )
        for(int i=0;i<3;i++)
            send[i] = i+1;

    if( rank == MPI_Root )  MPI_Send(&send[0],3,MPI_INTEGER,1,123,MPI_COMM_WORLD);
    // send 0 -> 1
    if( rank == 1 )  
    {   MPI_Recv(&send[0],3,MPI_INTEGER,MPI_Root,123,MPI_COMM_WORLD,&status);
        
        // if recv done add +1 for each elem
        for(int i=0;i<3;i++)
        {   printf("rank: %d\t %d\n",rank,send[i]);
            send[i]+=1;
        }

        MPI_Send(&send[0],3,MPI_INTEGER,MPI_Root,1414,MPI_COMM_WORLD);
    }
    
    if( rank == MPI_Root )
    {
        MPI_Recv(&recv[0],3,MPI_INTEGER,1,1414,MPI_COMM_WORLD,&status);

        for(int i=0;i<3;i++)
            printf("rank: %d\t %d\n",rank,recv[i]);

        MPI_Get_count(&status,MPI_INTEGER,&cnt);
        printf("\nsrc: %d\t tag: %d\t cnt: %d\n",
                status.MPI_SOURCE,status.MPI_TAG,cnt);
    }

    
    free(send); free(recv);

    MPI_Finalize();


    return 0;
}
