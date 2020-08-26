#include<stdio.h>
#include<time.h>
#include<mpi.h>
#include<gsl/gsl_blas.h>

int main(int argc,char* argv[])
{  
    srand((unsigned)time(NULL));
        
    const int root = 0;
    int numtasks, rank;
    double MPI_buffer[10];

    MPI_Request request;    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    
    gsl_vector* ws = gsl_vector_alloc(3);
    

    if( rank == root )
    {
        for(int i=0;i<ws->size;i++)   gsl_vector_set(ws,i,rand()%10);
        for(int i=0;i<ws->size;i++)   printf("%lf\t",gsl_vector_get(ws,i));
        printf("\n");
    
        for(int i=0;i<ws->size;i++)
        {   MPI_buffer[i] = gsl_vector_get(ws,i);
            printf("%lf\n",MPI_buffer[i]);
        }


        MPI_Isend(&MPI_buffer[0],ws->size,MPI_DOUBLE,1,1313,MPI_COMM_WORLD,&request);
        //MPI_Wait(&request,&status);
        printf("Here rank: %d, Isend: 1 is done\n",rank);


        MPI_Isend(&MPI_buffer[0],ws->size,MPI_DOUBLE,2,1414,MPI_COMM_WORLD,&request);
        //MPI_Wait(&request,&status);
        printf("Here rank: %d, Isend: 2 is done\n",rank);

        MPI_Irecv(&MPI_buffer[0],1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);
        printf("Recv done, the src was: %d\n",status.MPI_SOURCE);
        printf("Norm is: %lf\n",MPI_buffer[0]);


    }
    if( rank == 1 )
    {   
        MPI_Irecv(&MPI_buffer[0],ws->size,MPI_DOUBLE,root,1313,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);


        printf("Here rank: %d, Irecv is done\n the data is:",rank);
        for(int i=0;i<ws->size;i++)
        {   gsl_vector_set(ws,i,MPI_buffer[i]);
            printf("%lf\t",gsl_vector_get(ws,i));
        }   printf("\n");
    }
    if( rank == 2 )
    {
        for(int i=0;i<100000000;i++)
        {
            if( i%10000000 == 0 )
                printf("flag\n");
        }


        MPI_Irecv(&MPI_buffer[0],ws->size,MPI_DOUBLE,root,1414,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,&status);

        printf("Here rank: %d, Irecv is done\n the data is:",rank);
        for(int i=0;i<ws->size;i++)
        {   gsl_vector_set(ws,i,MPI_buffer[i]);
            printf("%lf\t",gsl_vector_get(ws,i));
        }   printf("\n");

        printf("now I will send the norm back to root\n");

        MPI_buffer[0] = gsl_blas_dnrm2(ws);

        MPI_Isend(&MPI_buffer[0],1,MPI_DOUBLE,root,1313,MPI_COMM_WORLD,&request);
        printf("here rank: %d, Isend over\n",rank);


    }


    



    gsl_vector_free(ws);

    MPI_Finalize();

    return 0;
}
