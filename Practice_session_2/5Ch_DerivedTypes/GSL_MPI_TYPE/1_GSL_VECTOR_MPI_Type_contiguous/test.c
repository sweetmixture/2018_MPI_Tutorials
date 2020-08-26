#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gsl/gsl_vector.h>
#include<mpi.h>

/*
typedef struct _gsl_vector
{
    ...
    int size;
    int stride;
    double* data;
    ...
}gsl_vector;
*/

int main(int argc, char* argv[])
{
    const int MPI_Root = 0;
    int numtasks,rank;

    /* What arguments need? */
    int blen[] = {1,1};   //for(int i=0;i<2;i++) printf("%d\n",blen[i]);
    MPI_Datatype oldtype[] = {MPI_DOUBLE,MPI_DOUBLE};
    MPI_Datatype newtype;
    MPI_Aint displs[2];

    gsl_vector* v = gsl_vector_alloc(2);    // continuesly allocated ! -> use MPI_Type_contiguous or vector?
    gsl_vector_set_zero(v);

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
/*    
    MPI_Address(&v->data[0],&displs[0]);
    MPI_Address(&v->data[1],&displs[1]);

    printf("%d\n",(displs[1]-displs[0])/sizeof(double));
*/
    if( rank == MPI_Root )
    {   for(int i=0;i<v->size;i++)
            gsl_vector_set(v,i,i+1);
    }   

    MPI_Type_contiguous(v->size,MPI_DOUBLE,&newtype);
    MPI_Type_commit(&newtype);
    
    MPI_Bcast(&v->data[0],1,newtype,0,MPI_COMM_WORLD);

    if( rank == 1 )
    {
        for(int i=0;i<v->size;i++)
            printf("%lf\t",gsl_vector_get(v,i));
        printf("\n");
    }


   
    MPI_Type_free(&newtype);
    gsl_vector_free(v);

    MPI_Finalize();
    return 0;
}
