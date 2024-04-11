//S2Q2, S3Q2, S10Q1, S12Q1
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 1000

int main(int argc, char** argv) {
	int rank;
	int arr[N];
	int local_sum = 0, global_sum = 0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0) {
		srand(time(NULL));
		for(int i=0; i<N; i++)
			arr[i] = rand() % 1000;
	}
	
	for(int i=0; i<N; i++)
		local_sum += arr[i];
		
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("Total sum is: %d\n", global_sum);
		printf("Average is: %ld\n", global_sum/N);
	}
	
	MPI_Finalize();
	
	return 0;
}

//mpicc mpi_1000_sum_avg.c -o mpi_1000_sum_avg
//mpirun -np 4 ./mpi_1000_sum_avg

