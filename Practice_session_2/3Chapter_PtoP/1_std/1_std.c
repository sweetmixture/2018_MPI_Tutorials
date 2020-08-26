#include<stdio.h>
#include<mpi.h>
#include<gsl/gsl_blas.h>

int main( int argc, char* argv[] )
{
    int numtasks, rank;
    const int root = 0;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Status state;

    double d[2] = {0,0};
    double c;
    gsl_vector* ws = gsl_vector_calloc(2);

    if( rank == root )
    {   gsl_vector_set(ws,0,4);
        gsl_vector_set(ws,1,3);
    
        for(int i=0;i<2;i++)
            d[i] = gsl_vector_get(ws,i);
        gsl_vector_free(ws);

        MPI_Send(&d[0],2,MPI_DOUBLE,1,13,MPI_COMM_WORLD);
    }
    
    if( rank == 1 )
    {
        MPI_Recv(&d[0],2,MPI_DOUBLE,root,13,MPI_COMM_WORLD,&state);

        // show stat 
        printf("here is rank: %d\t",rank);
        printf("Recv data from: %d\n",state.MPI_SOURCE);

        for(int i=0;i<2;i++)
            gsl_vector_set(ws,i,d[i]);
        
        d[0] = gsl_blas_dnrm2(ws);
        gsl_vector_free(ws);
    
        printf("nrm is: %lf\n",d[0]);
        printf("I will send this back to node 3\n");

        MPI_Send(&d[0],1,MPI_DOUBLE,2,1231,MPI_COMM_WORLD);
    }
    
    if( rank == 2)
    {   
        gsl_vector_free(ws);
        MPI_Recv(&d[0],1,MPI_DOUBLE,1,MPI_ANY_TAG,MPI_COMM_WORLD,&state);

        printf("here is rank: %d\t",rank);
        printf("Recv data from: %d\n",state.MPI_SOURCE);

        printf("The inside is: %lf\n",d[0]);
    }

    if( rank == root )
    {
    //    MPI_Recv(&c,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&state); // no sent data ----> DEAD LOCK
        printf("Here is rank: %d\n",rank);
        printf("Recv data from: %d\n",state.MPI_SOURCE);    

        printf("The inside is: %lf\n",c);
    }





    MPI_Finalize();
    return 0;
}
