#include<stdio.h>
#include<mpi.h>
#include<gsl/gsl_blas.h>



/// IRECV* + SEND + WAIT* ---> SAFE

int main( int argc, char* argv[] )
{   
    int numtasks, rank;
    const int root = 0.;

    double MPI_Buffer[10];
    double MPI_B_Recv[10];
    gsl_vector* v = gsl_vector_alloc(3);

    MPI_Request request;   MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if( rank == root )
    {
        for(int i=0;i<10;i++)
            MPI_Buffer[i] = i+1;
    }
    else
    {  
        for(int i=0;i<10;i++)
            MPI_Buffer[i] = i+10;
    }

    
    if( rank == root )
    {
        MPI_Irecv(&MPI_B_Recv[0],10,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&request);
     // MPI_Wait(&request,&status);

        MPI_Send(&MPI_Buffer[0],10,MPI_DOUBLE,1,13,MPI_COMM_WORLD);

        MPI_Wait(&request,&status);                                 // Irecv* + Send + Wait* routine
        printf("root recv done, src: %d\n",status.MPI_SOURCE);
        for(int i=0;i<10;i++)   printf("%lf\n",MPI_B_Recv[i]);

        
        printf("root send done\n");
    }
    if( rank == 1 )
    {
        MPI_Irecv(&MPI_B_Recv[0],10,MPI_DOUBLE,root,13,MPI_COMM_WORLD,&request);
     // MPI_Wait(&request,&status);
        
        MPI_Send(&MPI_Buffer[0],10,MPI_DOUBLE,root,15125,MPI_COMM_WORLD);


        MPI_Wait(&request,&status);
        printf("rank 1 recv done, src: %d\n",status.MPI_SOURCE);
        for(int i=0;i<10;i++)   printf("%lf\n",MPI_B_Recv[i]);
    }

    MPI_Finalize();

    gsl_vector_free(v);


    return 0;
}
