#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

typedef struct
{
    int buf[2];
    double dbuf[3];
}Val;

int main(int argc, char* argv[])
{
    const int MPI_Root = 0;
    int numtasks,rank;
/*    
    struct _val 
    {   int buf[2];
        double dbuf[3];
    }val;
*/
    Val val;

    /* What arguments need? */
    int blen[] = {2,3};   //for(int i=0;i<2;i++) printf("%d\n",blen[i]);
    MPI_Datatype oldtype[] = {MPI_INTEGER,MPI_DOUBLE};
    MPI_Datatype newtype;
    MPI_Aint displs[2];


    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    // APPLICATION OF "MPI_Address()"
    MPI_Address( &val.buf[0], &displs[0] ); printf("%d\n",displs[0]);
    MPI_Address( &val.dbuf[0], &displs[1] );
    displs[1] = displs[1] - displs[0];
    displs[0] = 0;                      // Get starting indices ... with MPI_Address trick  
                                        // Surely, without the support of MPI_Address(), the distance (in byte unit) 
                                        // between val.buf[0] and val.dbuf[0] cannot be obtained

    MPI_Type_struct(2,blen,displs,oldtype,&newtype);
    MPI_Type_commit(&newtype);


    if( rank == MPI_Root )
    {   for(int i=0;i<2;i++) val.buf[i] = i+1;
        for(int i=0;i<3;i++) val.dbuf[i] = i+1;
    }
    else
    {   memset(&val.buf[0],0,2*sizeof(int));
        memset(&val.dbuf[0],0,2*sizeof(double));
    }
    
    // test print b4 Bcast
    if( rank == 1 )
    {   printf("test print b4 Bcast call\n");
        for(int i=0;i<2;i++) printf("buf[%d]:%d\n",i,val.buf[i]);
        for(int i=0;i<3;i++) printf("dbuf[%d]:%lf\n",i,val.dbuf[i]);
        printf("\n");
    }
    
    MPI_Bcast(&val,1,newtype,MPI_Root,MPI_COMM_WORLD);

    if( rank == 1 )
    {   printf("test print after Bcast call\n");
        for(int i=0;i<2;i++) printf("buf[%d]:%d\n",i,val.buf[i]);
        for(int i=0;i<3;i++) printf("dbuf[%d]:%lf\n",i,val.dbuf[i]);
        printf("\n");
    }

    MPI_Type_free(&newtype);

    MPI_Finalize();

    return 0;
}
