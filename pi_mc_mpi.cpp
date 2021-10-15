#include <iostream>
#include <iomanip>
#include <mpi.h>
#define MASTER 0
#define SEED 35791246

using namespace std;

int main(int argc, char **argv)
{
    int nprocs, rank, N, chunksize, val;
    double partial_dotprod, stime, etime;

    // MPI Init and rank
    // Your code
    MPI_Status Stat;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == MASTER)
        stime = MPI_Wtime(); // start time

    // Get N
    N = atoi(argv[1]);

    // Calculate number of chunksize for each rank
    // Your code
    chunksize = N/nprocs;
    if (rank == MASTER)
        chunksize = chunksize + N % nprocs;
    // You should consider N is not divided nprocs

    // Populate and initialize x and y vectors using chunk size

    // Your code
    double x[chunksize], y[chunksize];
    for (int i=0; i < chunksize; i++){
        x[i]=1.0;
        y[i]=1.0;
    
    }

    if (rank == MASTER) // I am MASTER
    {
        //perform the partial dot product for each rank
        for(int i = 0; i<chunksize; i++)
        partial_dotprod +=x[i]*y[i];
        
        // Your code
        //

        for (int dest_rank = 1; dest_rank < nprocs; dest_rank++)
        {
            MPI_Status status;
            MPI_Recv(&val, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            circle_count += val;
        }
        pi = 4 * circle_count / double(npoints);

        etime = MPI_Wtime(); // end time
        cout<< "  " << setw(10) << "N"
            << "  " << setw(10) << "dot product"
            << "  " << setw(10) << "nprocs"
            << "  " << setw(30) << "elapsed wall-clock time" << "\n";
        cout << "  " << setw(10) << N
            << "  " << setw(10) << partial_dotprod
            << "  " << setw(10) << nprocs
            << "  " << setw(30) << etime-stime << "\n";
    }
    else  // I am WORKER
    {
        // Your code
        MPI_Send(&circle_count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    }

    // MPI finalize
    MPI_Finalize();
}