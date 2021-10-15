#include <iostream>
#include <cstdlib>     // has exit(), etc.
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <mpi.h>
#define MASTER 0

#define MAX_ORDER 4
typedef float LOCAL_MATRIX_T[MAX_ORDER][MAX_ORDER];



void Read_vector(float local_x[], int local_n, int rank, int p );
void Read_matrix(LOCAL_MATRIX_T local_A, int local_m, int n, int rank, int p );
void Parallel_matrix_vector_prod( LOCAL_MATRIX_T local_A, int m, int n, float local_x[], float global_x[], float local_y[], int local_m, int local_n, int rank);

void Print_matrix(LOCAL_MATRIX_T local_A, int local_m, int n, int rank, int p );

void Print_vector(float local_y[], int local_m, int rank, int p );




int main(int argc, char **argv)
{
  
  int rank, p;
	LOCAL_MATRIX_T local_A;
	float global_x[MAX_ORDER], local_x[MAX_ORDER], local_y[MAX_ORDER];
	int m, n, local_m, local_n;

  // MPI init
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Initialize matrix
  if (rank == MASTER) {
    printf("// Just simply set N(4) X M(4) matrix and M(4) X 1 vector\n");
		scanf("%d %d", &n, &m);
//input M=4,N=4

	}

	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	local_m = m/p;
	local_n = n/p;
	Read_matrix(local_A, local_m, n, rank, p);
	Print_matrix(local_A, local_m, n, rank, p);
	Read_vector(local_x, local_n, rank, p);
	Print_vector(local_x, local_n, rank, p);
	Parallel_matrix_vector_prod(local_A, m, n, local_x, global_x, local_y, local_m, local_n, rank);
	Print_vector(local_y, local_m, rank, p);


  MPI_Finalize();  // MPI finalize

  return 0;     // Exit 
  } 

  // MPI Scatter the A Matrix
void Read_matrix(LOCAL_MATRIX_T local_A, int local_m, int n, int rank, int p )
{	int i, j;
	LOCAL_MATRIX_T temp={{0},};
	/* Fill dummy entries in temp with zeroes */
	for (i = 0; i < p*local_m; i++)
		for (j = n; j < MAX_ORDER; j++)
			temp[i][j] = 0.0;
	if (rank == 0)
	{	printf("%s\n");
		for (i = 0; i < p*local_m; i++)
			for (j = 0; j < n; j++)
				scanf("%f",&temp[i][j]);
	}

	MPI_Scatter(temp, local_m*MAX_ORDER, MPI_FLOAT, local_A, local_m*MAX_ORDER, MPI_FLOAT, 0, MPI_COMM_WORLD);
}


  // Broadcast the B vector
void Read_vector(float local_x[], int local_n, int rank, int p )
{	int i;
	float temp[MAX_ORDER];
	if (rank == 0)
	{	printf("%s\n");
		for (i = 0; i < p*local_n; i++)
			scanf("%f", &temp[i]);
	}
	// same as above for read_matrix(). has to be called by each process like mpi_bcast()
	MPI_Scatter(temp, local_n, MPI_FLOAT, local_x, local_n, MPI_FLOAT, 0, MPI_COMM_WORLD);
}

  // Calculate Xpart
    // MPI Gather
void Parallel_matrix_vector_prod( LOCAL_MATRIX_T local_A, int m, int n, float local_x[], float global_x[], float local_y[], int local_m, int local_n, int rank)
{	/* local_m = m/p, local_n = n/p */
	int i, j;

	MPI_Allgather(local_x, local_n, MPI_FLOAT, global_x, local_n, MPI_FLOAT, MPI_COMM_WORLD);

	for (i = 0; i < local_m; i++)
	{	local_y[i] = 0.0;
		for (j = 0; j < n; j++)
			local_y[i] = local_y[i] + local_A[i][j]*global_x[j];
	}
}

void Print_matrix(LOCAL_MATRIX_T local_A, int local_m, int n, int rank, int p )
{	int i, j;
	float temp[MAX_ORDER][MAX_ORDER];
	MPI_Gather(local_A, local_m*MAX_ORDER, MPI_FLOAT, temp, local_m*MAX_ORDER, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{	printf("%s\n");
		for (i = 0; i < p*local_m; i++)
		{	for (j = 0; j < n; j++)
				printf("%4.1f ", temp[i][j]);
			printf("\n");
		}
	} 
}
  
  // Print results
void Print_vector(float local_y[], int local_m, int rank, int p )
{	int i;
	float temp[MAX_ORDER];
	// has to be called by each process like mpi_bcast()
	MPI_Gather(local_y, local_m, MPI_FLOAT, temp, local_m, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{	printf("%s\n");
		for (i = 0; i < p*local_m; i++)
			printf("%4.1f ", temp[i]);
		printf("\n");
	}
}