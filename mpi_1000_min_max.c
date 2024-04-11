//S5Q2, S11Q2, S16Q2, S20Q2 
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <limits.h>

#define N 1000

int main(int argc, char** argv) {
	int rank;
	int arr[N];
	int local_min = INT_MAX, local_max = INT_MIN;
	int global_min, global_max;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0) {
		srand(time(NULL));
		for(int i=0; i<N; i++)
			arr[i] = rand() % 1000;
	}
	
	for(int i=0; i<N; i++) {
		if(arr[i] < local_min) {
			local_min = arr[i];
		}
		if(arr[i] > local_max) {
			local_max = arr[i];
		}
	}
		
	MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("Min: %d\n", global_min);
		printf("Max: %d\n", global_max);
	}
	
	MPI_Finalize();
	
	return 0;
}

//mpicc mpi_1000_min_max.c -o mpi_1000_min_max
//mpirun -np 4 ./mpi_1000_min_max

