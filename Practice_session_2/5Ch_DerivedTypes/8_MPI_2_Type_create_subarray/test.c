#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<gsl/gsl_vector.h>
#include<mpi.h>

int main(int argc, char* argv[])
{
    const int MPI_Root = 0;
    int numtasks,rank;

    double h[3][3];

    int array_of_sizes[2];  // 2d array
    int array_of_subsizes[2];
    int array_of_starts[2];

    array_of_sizes[0] = 3; array_of_sizes[1] = 3; // 3x3 matrix
    // if we wanna copy and transfer left bottom square matrix ... 2x2 matrix
    array_of_subsizes[0] = 2; array_of_subsizes[1] = 2;
    array_of_starts[0] = 1; array_of_starts[1] = 0;

    MPI_Datatype newtype;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if( rank == MPI_Root )
    {   for(int i=0;i<3;i++)
        {   for(int j=0;j<3;j++)
                h[i][j] = i*3+j+1;
        }
    }

    MPI_Type_create_subarray(2, array_of_sizes, array_of_subsizes, array_of_starts, MPI_ORDER_C, MPI_DOUBLE, &newtype);
    MPI_Type_commit(&newtype);

    MPI_Bcast(&(h[0][0]),1,newtype,0,MPI_COMM_WORLD);

    if( rank != MPI_Root )
    {
        for(int i=0;i<3;i++)
        {   for(int j=0;j<3;j++)
                printf("%lf\t",h[i][j]);
            printf("\n");
        }
    }

    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}
