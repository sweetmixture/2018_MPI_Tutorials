#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<mpi.h>
#include<gsl/gsl_blas.h>

#define SIZE 5

int main( int argc, char* argv[] )
{
    srand((unsigned)time(NULL));

    const int MPI_Root = 0;
    int numtasks, rank;

    double* MPI_Send_ws = (double*)calloc(SIZE,sizeof(double));
    double* MPI_Recv_ws = (double*)calloc(SIZE,sizeof(double));
    
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    
    if( rank == MPI_Root )
    {   for(int i=0;i<SIZE;i++)
        {   MPI_Send_ws[i] = rand()%SIZE;
            printf("%lf\n",MPI_Send_ws[i]);
        }

        printf("Above show data in root proc\n");
    }

    MPI_Bcast(MPI_Send_ws,SIZE,MPI_DOUBLE,MPI_Root,MPI_COMM_WORLD); // CALL MPI_BCAST
    

    for(int i=0;i<numtasks;i++)
    {
        if( i != MPI_Root && i == rank )
        {   printf("idx: %d\n",i);
            printf("Recv done in proc: %d\n",rank);
            for(int j=0;j<SIZE;j++)
                printf("%lf\n",MPI_Send_ws[j]);
        }
    }

    MPI_Finalize();

    free(MPI_Send_ws);  free(MPI_Recv_ws);


    return 0;
}
