#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

#define MAX(a,b) ((a)>=(b)?(a):(b))
#define MIN(a,b) ((a)>=(b)?(b):(a))

#define IN
#define OUT

#define SIZE 10

#define MPI_Root 0

void MPI_Support_block_dis( IN const int tot_iter, IN const int numtasks,
        IN const int rank, OUT int* ista, OUT int* iend )
{
    *ista = 0;  *iend = 0;
    
    int Q = tot_iter/numtasks;  // quotient
    int R = tot_iter%numtasks;  // residue

    *ista = Q*rank + MIN(R,rank);
    *iend = *ista + Q;

    if(R>rank)
        (*iend)++;
//    printf("rank: %d\t ista: %d\t iend: %d\n",rank, *ista, *iend);
    return;
}


int main(int argc, char* argv[])
{
    int rank, numtasks;
    
    int* data = NULL;
    int* collect = NULL;

    int ista, iend;
    int* rcnt;
    int* displs;

//    printf("argv[0]: %s\n",argv[0]);
//    printf("argv[1]: %s\n",argv[1]);
//    printf("atoi(argv[1]: %d\n",atoi(argv[1]));


    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    data = (int*)calloc(SIZE,sizeof(int));
    collect = (int*)calloc(SIZE,sizeof(int));
    displs = (int*)calloc(numtasks,sizeof(int));
    rcnt   = (int*)calloc(numtasks,sizeof(int));

    MPI_Support_block_dis(SIZE,numtasks,rank,&ista,&iend);
    
    printf("rank: %d\t ista: %d\t iend: %d\n",rank,ista,iend);


    for(int i=ista;i<iend+1;i++)
    {   collect[i] = i+1;
    //    printf("%d\n",collect[i]);
    }
/*
    if( rank == MPI_Root )
    {   for(int i=0;i<SIZE;i++)
            printf("%d\n",collect[i]);
    }
    else if( rank == 1 )
    {   for(int i=0;i<SIZE;i++)
            printf("%d\n",collect[i]);
    }
    else
    {   for(int i=0;i<SIZE;i++)
            printf("%d\n",collect[i]);
    }
*/


//    MPI_Bcast(&collect[ista],iend-ista+1,MPI_INTEGER,rank,MPI_COMM_WORLD);    // not working
// BCAST TO GATHER DATA INTO ROOT PROCESSOR // -> Gatherv routine
//    printf("MPI_Bcast(&collect[%d],%d,MPI_INTEGER,%d,MPI_COMM_WORLD)\n",
//           ista,iend-ista+1,rank);



//    MPI_Bcast(&collect[0],4,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);

/*
    MPI_Gather(&collect[ista],iend-ista+1,MPI_INTEGER,
            &data[0],iend-ista+1,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);
*/

    rcnt[rank] = iend-ista+1;
    displs[rank] = ista;    // for Gatherv routine
    for(int i=0;i<numtasks;i++)
    {   MPI_Bcast(&rcnt[i],1,MPI_INTEGER,i,MPI_COMM_WORLD);
        MPI_Bcast(&displs[i],1,MPI_INTEGER,i,MPI_COMM_WORLD);
    }



    for(int i=0;i<10000000;i++)
        continue;

    // make int* rcnt, int* displs as public array

    if(rank==MPI_Root)
    {
        for(int i=0;i<numtasks;i++)
            printf("rcnt[%d]: %d, displs[%d]: %d\n",i,rcnt[i],i,displs[i]);

    }
//    rcnt[0] = 5; rcnt[1] =5;
//    displs[0] = 0; displs[1] = 5;


    for(int i=0;i<10000000;i++)
        continue;

    printf("rank: %d\t rcnt[%d]:%d\t displs[%d]:%d\n",
        rank,rank,rcnt[rank],rank,displs[rank]);
    
    MPI_Gatherv(&collect[ista],iend-ista+1,MPI_INTEGER,
            &collect[0],rcnt,displs,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);
          

    for(int i=0;i<10000000;i++)
        continue;

    if(rank == MPI_Root)
    {
        puts("");
        printf("After Bcast in Root\n");
        for(int i=0;i<SIZE;i++)
            printf("%d\t %d\n",data[i],collect[i]);
    }



/*
    for(int i=0;i<numtasks;i++)
    {
        if( rank == i )
        {
            printf("rank %d\n",rank);

            for(int j=0;j<SIZE;j++)
                printf("%d\n",collect[i]);
            puts("");
        }
    }
*/    




    free(data); free(collect);  free(displs);   free(rcnt);

    MPI_Finalize();
    
    return 0;
}
