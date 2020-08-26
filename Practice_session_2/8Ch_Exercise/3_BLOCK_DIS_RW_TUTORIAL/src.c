#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<mpi.h>

#define IN
#define OUT
#define MPI_Root 0

#define MIN(a,b) ((a)>=(b)?(b):(a))

#define MAXPTC 100000
#define MAXCYCLE 100000
#define MAXDIS 10000

void MPI_Support_block_dis( IN const int tot_iter, IN const int numtasks,
        IN const int rank, OUT int* ista, OUT int* iend )
{
    *ista=0; *iend=0;

    int q = tot_iter/numtasks; //quotient
    int r = tot_iter%numtasks; //residue

    *ista = q*rank + MIN(r,rank);
    *iend = *ista + q;

    if( r > rank )
        (*iend)++;

    return;
}

int main(int argc, char* argv[])
{   
    // time estimator
    clock_t start, end;

    //RW Parameters
    const float BC=1.;
    const float DeltaE=1.;
    int program_time=1;
    int ptc[MAXPTC];
    float T;
    int MAX_R, MAX_L;
    int disneg[MAXDIS], dispos[MAXDIS];

    // File write parameters
    FILE* fp = NULL;
    char FNBUFFER[40];

    
    //MPI Parameters
    int rank, numtasks;
    int ista, iend;
    int* rcnt=NULL;
    int* displs=NULL;


    //Initialising arrays
    memset(ptc,0,MAXPTC*sizeof(int));
    memset(disneg,0,MAXDIS*sizeof(int));
    memset(dispos,0,MAXDIS*sizeof(int));


    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    srand((unsigned)time(NULL)+rank*numtasks);  // give different seed by the extra + rank*numtasks

    if( rank == MPI_Root )
    {   
        start = clock();
        printf("Eneter the temperature want to scan... \n");
        scanf("%f",&T);
    }
    MPI_Bcast(&T,1,MPI_FLOAT,MPI_Root,MPI_COMM_WORLD);  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    rcnt = (int*)calloc(numtasks,sizeof(int));
    displs = (int*)calloc(numtasks,sizeof(int));

    // setup MPI parameters
    MPI_Support_block_dis(MAXPTC,numtasks,rank,&ista,&iend);
    rcnt[rank] = iend-ista+1;
    displs[rank] = ista;
    for(int i=0;i<numtasks;i++)
    {   MPI_Bcast(&rcnt[i],1,MPI_INTEGER,i,MPI_COMM_WORLD);
        MPI_Bcast(&displs[i],1,MPI_INTEGER,i,MPI_COMM_WORLD);   }   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    printf("rank: %d\t ista: %d\t iend: %d\n",rank,ista,iend);
    printf("rcnt[%d]:%d\t displs[%d]:%d\n",rank,rcnt[rank],rank,displs[rank]);
  // chk point - 1

    for(int i=0;i<MAXCYCLE;i++) // MAIN CYCLE
    {
        for(int j=ista;j<iend;j++)  // BLOCK DISTED NEDTED LOOP -> PTC  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        {
            if( exp(-DeltaE/((BC)*T)) > (float)rand()/RAND_MAX )
            {   // ACCEPT
                if( rand() < RAND_MAX/2 )
                    ptc[j]++;   // move forward
                else
                    ptc[j]--;   // move backward
            }
            // else REJECT
        }// END PTC             //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        if( rank == MPI_Root )
            printf("CHK POINT\t %d done\n",i+1);
        program_time++;
    }// END MAIN CYCLE
   
    
    // MPI_Gaterv ... collect all data into MPI_Root
    MPI_Gatherv(&ptc[ista],iend-ista+1,MPI_INTEGER,
            &ptc[0],rcnt,displs,MPI_INTEGER,MPI_Root,MPI_COMM_WORLD);   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    MPI_Barrier(MPI_COMM_WORLD);
/*    puts("FLAG-1");
    
    if(rank == MPI_Root)
    {
        for(int i=0;i<MAXPTC;i++)
            printf("ptc[%d]: %d\n",i,ptc[i]);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    puts("FLAG-2");
*/

    // Histogram Make       all the rest in the master node
    if( rank == MPI_Root )
    {   
        MAX_R = 0; MAX_L = 0;   // init RL limit parameters
        for(int i=0;i<MAXPTC;i++)
        {   
            if( ptc[i] > 0 )
            {
                dispos[ ptc[i] ] += 1;
                if( ptc[i] > MAX_R )
                    MAX_R = ptc[i];
            }
            else
            {
                disneg[ -ptc[i] ] += 1;
                if( -ptc[i] > MAX_L )
                    MAX_L = -ptc[i];
            }
        }

        //printf("MAX_L: %d\t MAX_R: %d\n",MAX_L,MAX_R);


        sprintf(FNBUFFER,"%s_%d","Distribution",program_time);
        fp = fopen(FNBUFFER,"w");
        fprintf(fp,"#TIME(PASSED): %d\t%fK\n",program_time,T);

        for(int i=MAX_L;i>0;i--)
        {
            if( disneg[i] > 0 )
                fprintf(fp,"%d\t%d\n",-i,disneg[i]);
        }
        
        for(int i=0;i<MAX_R;i++)
        {
            if( dispos[i] > 0 )
                fprintf(fp,"%d\t%d\n",i,dispos[i]);
        }

        fclose(fp);


        end = clock();

        printf("CPU time used: %lf\n", (double)(end-start)/CLOCKS_PER_SEC);
    }// Histogram Done

    free(rcnt);free(displs);

    MPI_Finalize();


    return 0;
}
