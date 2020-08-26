#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define MIN(a,b) ((a)>=(b)?(b):(a))
#define IN
#define OUT

void MPI_CUSTOM_BLOCK_DIS( IN const int numiter, IN const int numtasks, IN const int rank,
        OUT  int* ista, OUT int* iend )
{
    /* init */
    *ista = 0; *iend = 0;

    int L = numiter/numtasks;
    int R = numiter%numtasks;

    *ista = L*rank + MIN( R, rank );
    *iend = *ista + L;
    
    if( R > rank )
        (*iend)++;

  //  printf("ista: %d\t iend: %d\t rank: %d\n",*ista,*iend,rank);
    return;
}


int main(int argc, char* argv[])
{
    const int MPI_Root = 0;

    int numtasks, rank;
    int ista, iend;

    int comm_int_s[30];
    int comm_int_r[30];
    memset(comm_int_s,0,30*sizeof(int));
    memset(comm_int_r,0,30*sizeof(int));

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

//    for(int i=ista;i<iend;i++)
//        comm_int_s[i] = i+1;

    MPI_CUSTOM_BLOCK_DIS( 30, numtasks, rank, &ista, &iend );

 //   printf("ista: %d\t iend: %d\t rank: %d\n",ista,iend,rank);


    for(int i=ista;i<iend;i++)
        comm_int_s[i] = i;


    
    for(int i=0;i<numtasks;i++)
    {   if( rank == i )
        {   printf("rank: %d\n",rank);
            for(int j=0;j<30;j++)
                printf("%d\n",comm_int_s[j]);
        }
    }

    MPI_Finalize();

    return 0;
}
