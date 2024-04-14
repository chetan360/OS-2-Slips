//S21Q2, S22Q1
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 1000

int main(int argc, char** argv) {
	int rank, n;
	int arr[N];
	int local_even_sum = 0, global_even_sum = 0;
	int local_odd_sum = 0, global_odd_sum = 0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	
	if(rank == 0) {
		srand(time(NULL));
		for(int i=0; i<N; i++)
			arr[i] = rand() % 1000;
	}
	
	for(int i=0; i<N; i++) {
		if(arr[i] % 2 == 0)
			local_even_sum += arr[i];
		else
			local_odd_sum += arr[i];
	}
		
	MPI_Reduce(&local_even_sum, &global_even_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_odd_sum, &global_odd_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("Total even sum is: %d\n", global_even_sum);
		printf("Total odd sum is: %d\n", (float)global_odd_sum);
	}
	
	MPI_Finalize();
	
	return 0;
}

//mpicc mpi_1000_sum_odd_even.c -o mpi_1000_sum_odd_even
//mpirun -np 4 ./mpi_1000_sum_odd_even

