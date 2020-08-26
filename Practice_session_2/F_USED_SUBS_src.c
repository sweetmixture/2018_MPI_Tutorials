

/* SIMPLE BLOCK DISTRIBUTOR */

#define MIN(a,b) ((a)>=(b)?(a):(b))

#define IN
#define OUT

void MPI_Support_block_dis( IN const int total_iteration, IN const int numtasks, IN const int rank, OUT int* ista, OUT int* iend )
{
    *ista = 0; *iend = 0;

    int Q = total_iteration/numtasks; //quotient
    int R = total_iteration%numtasks; //residue

    *ista = Q*rank + MIN(R,rank);
    *iend = *ista + Q;

    if( R > rank )
        (*iend)++;

    return;
}


// 















/* SIMPLE BLOCK DISTRIBUTOR END */
