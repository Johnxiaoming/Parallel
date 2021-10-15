#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <mpi.h>

#define MASTER 0

using namespace std;

double dotProduct(double *x, double *y, int n) {
  int i;
  double prod = 0.0;
  for (i = 0; i < n; i++) {
    prod += x[i]*y[i];
  }
  return prod;
}

int main(int argc, char *argv[]) {
  int i,N;
  double prod;
  int my_rank;
  int num_procs;
  double stime, etime;
 
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == MASTER)
        stime = MPI_Wtime(); // start time

    // Get N
    N = atoi(argv[1]);

    // Calculate number of chunksize for each rank
    // Your code
   
   
  int local_N = N / num_procs; 
   if (my_rank == MASTER)
        local_N = N + N % num_procs;//assuming N is totally divisible by num_procs  
  double local_x[local_N];
  double local_y[local_N];
  for(i = 0; i < local_N; i++) {
    local_x[i] = 0.01 * (i + my_rank * local_N);
    local_y[i] = 0.03 * (i + my_rank * local_N);
  }
  double local_prod;
  local_prod = dotProduct(local_x,local_y,local_N);
  MPI_Reduce(&local_prod, &prod, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  if (my_rank == MASTER) {
            etime = MPI_Wtime(); // end time
        cout<< "  " << setw(10) << "N"
            << "  " << setw(10) << "dot product"
            << "  " << setw(10) << "nprocs"
            << "  " << setw(30) << "elapsed wall-clock time" << "\n";
        cout << "  " << setw(10) << N
            << "  " << setw(10) << N
            << "  " << setw(10) << num_procs
            << "  " << setw(30) << etime-stime << "\n";
  }  
  MPI_Finalize();

  return 0;
}