#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gsl/gsl_vector.h>
#include<mpi.h>

typedef struct _Dummy
{   int ccc;
    int c[3];
    double d[3];
}Dummy;

int main(int argc, char* argv[])
{
    const int MPI_Root = 0;
    int numtasks,rank;

    /* Required Arguments */
    int blen[] = {3,3};   //for(int i=0;i<2;i++) printf("%d\n",blen[i]);
    MPI_Datatype oldtype[] = {MPI_INTEGER,MPI_DOUBLE};
    MPI_Datatype newtype;
    MPI_Aint displs[2];

    Dummy* v = (Dummy*)malloc(sizeof(Dummy));

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    //APPLICATION OF "MPI_Address()"
    MPI_Address(&v->c[0],&displs[0]);
    MPI_Address(&v->d[0],&displs[1]);
    displs[1] = displs[1] - displs[0];
    displs[0] = 0;

    MPI_Type_struct(2,blen,displs,oldtype,&newtype);
    MPI_Type_commit(&newtype);


    if( rank == MPI_Root )
    {   for(int i=0;i<3;i++)
        {   v->c[i] = i + 1;
            v->d[i] = i + 3;    }
    }
    else
    {
        memset(&v->c[0],0,3*sizeof(int));
        memset(&v->d[0],0,3*sizeof(double));
    }

    // test print b4 Bcast
    if( rank == 1 )
    {   printf("test print b4 Bcast call\n");
        for(int i=0;i<3;i++)
        {   printf("c[%d]: %d\n",i,v->c[i]);
            printf("d[%d]: %lf\n",i,v->d[i]);
        }
    }
    
    MPI_Bcast(&v->c[0],1,newtype,MPI_Root,MPI_COMM_WORLD);
    /* equivalent */ //MPI_Bcast(v,1,newtype,MPI_Root,MPI_COMM_WORLD);

    if( rank == 1 )
    {   
        printf("test print after Bcast call\n");
        for(int i=0;i<3;i++)
        {   printf("c[%d]: %d\n",i,v->c[i]);
            printf("d[%d]: %lf\n",i,v->d[i]);
        }
    }

    MPI_Type_free(&newtype);
    free(v);

    MPI_Finalize();
    return 0;
}
