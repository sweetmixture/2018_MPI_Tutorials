#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

#define MPI_Root 0

/* BASED ON THE MPI ROUTINES :
 * 
 * MPI_Get_address();
 * MPI_Type_create_struct();
 *
 * MPI above v 2.0.4
 */

typedef struct
{
    double c[3];
    double f[3];
    double h[3][3];
    double e;
}PTC;

void MPI_Support_displs(void* displs, const int cnt );

int main(int argc,char* argv[])
{
    int numtasks, rank;
    
    MPI_Aint displs[4];
    MPI_Datatype oldtype[] = {MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE};
    int blen[] = {3,3,9,1};
    MPI_Datatype newtype;
    
    PTC* ptc = (PTC*)malloc(sizeof(PTC));
    memset(&ptc->c[0],0,3*sizeof(double));
    memset(&ptc->f[0],0,3*sizeof(double));
    for(int i=0;i<3;i++)
        memset(&ptc->h[i],0,3*sizeof(double));

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    MPI_Get_address(&ptc->c[0],&displs[0]);
    MPI_Get_address(&ptc->f[0],&displs[1]);
    MPI_Get_address(&ptc->h[0][0],&displs[2]);
    MPI_Get_address(&ptc->e,&displs[3]);
/*
    displs[3] = displs[3] - displs[0];
    displs[2] = displs[2] - displs[0];
    displs[1] = displs[1] - displs[0];
    displs[0] = 0;
*/
    MPI_Support_displs(&displs[0],4);
    printf("%ld\t %ld\t %ld\t %ld\n\n",displs[3],displs[2],displs[1],displs[0]);

    MPI_Type_create_struct(4,blen,displs,oldtype,&newtype);
    MPI_Type_commit(&newtype);

    if(rank == MPI_Root)
    {
        for(int i=0;i<3;i++)
        {   for(int j=0;j<3;j++)
                ptc->h[i][j] = i*3+j;
        }
    }

    MPI_Bcast(&ptc->c[0],1,newtype,MPI_Root,MPI_COMM_WORLD);
    // Bcast done

    if(rank != MPI_Root)
    {
        for(int i=0;i<3;i++)
        {   for(int j=0;j<3;j++)
                printf("%lf\t",ptc->h[i][j]);
            puts("");
        }
    }

    MPI_Type_free(&newtype);

    MPI_Finalize();

    free(ptc);

    return 0;
}

void MPI_Support_displs(void* displs, const int cnt )
{
    MPI_Aint* dummy = (MPI_Aint*)displs;

    for(int i=cnt-1;i>0;i--)
        dummy[i] = dummy[i] - dummy[0];

    dummy[0] = 0;

    return;
}
