//S2Q1, S11Q1
#include <stdio.h>

#define M 5
#define N 4

void accAvailable(int available[N]) {
	for(int i=0; i<N; i++) {
		scanf("%d", &available[i]);
	}
}

void displayAllocationNMax(int allocation[M][N], int max[M][N]) {
	printf("Enter allocation:\n");
	for(int i=0; i<M; i++) {
		for(int j=0; j<N; j++) {
			scanf("%d", &allocation[i][j]);
		}
	}
	
	printf("Enter max:\n");
	for(int i=0; i<M; i++) {
		for(int j=0; j<N; j++) {
			scanf("%d", &max[i][j]);
		}
	}
	
	printf("Allocation:\n");
	for(int i=0; i<M; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ", allocation[i][j]);
		}
		printf("\n");
	}
	
	printf("Max:\n");
	for(int i=0; i<M; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ", max[i][j]);
		}
		printf("\n");
	}
}

void findNDisplayNeed(int allocation[M][N], int max[M][N], int need[M][N]) {
	for(int i=0; i<M; i++) {
		for(int j=0; j<N; j++) {
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	
	for(int i=0; i<M; i++) {
		for(int j=0; j<N; j++) {
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}
}

void diplayAvailable(int available[N]) {
	for(int i=0; i<N; i++) {
		printf("%d ", available[i]);
	}
}

int safty(int available[N], int allocation[M][N], int need[M][N], int safeSeq[M]) {
	int work[N];
	for(int i=0; i<N; i++) {
		work[i] = available[i];
	}
	
	int finish[M];
	for(int i=0; i<M; i++) {
		finish[i] = 0;
	}
	
	int done = 0;
	while(done < M) {
		int found = 0;
		for(int i=0; i<M; i++) {
			if(!finish[i]) {
				int j;
				for(j=0; j<N; j++) {
					if(need[i][j] > work[j]) {
						break;
					}
				}
				
				if(j == N) {
					for(int k=0; k<N; k++) {
						work[k] += allocation[i][k];
					}
					safeSeq[done] = i;
					done++;
					finish[i] = 1;
					found = 1;
				}
			}
		}
		if(!found) {
			return 0;
		}
	}
	
	return 1;
}

int main() {
	int ch;
	int available[N], allocation[M][N], max[M][N], need[M][N]; 
	
	do {
		printf("\n\nMenu\n");
		printf("1. Accept Available.\n");
		printf("2. Display Allocation, Max.\n");
		printf("3. Find need and display it.\n");
		printf("4. Display Available.\n");
		printf("5. Exit.\n\n");
		
		printf("Enter your choise: ");
		scanf("%d", &ch);
		
		switch(ch) {
			case 1: accAvailable(available);
				break;
			case 2: displayAllocationNMax(allocation, max);
				break;
			case 3: findNDisplayNeed(allocation, max, need);
				break;
			case 4: diplayAvailable(available);
				break;
		}
	} while(ch != 5);
	
	int  safeSeq[M];
	if(safty(available, allocation, need, safeSeq)) {
		printf("System is in safe state. Safe sequence: ");
		for(int i=0; i<M; i++) {
			printf("P%d ", safeSeq[i]);
		}
		printf("\n");
	} else {
		printf("System is deadlocked.");
	}
	
	return 0;
}

