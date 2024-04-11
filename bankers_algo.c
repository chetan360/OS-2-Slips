//S4Q1, S1Q1, S3Q1, S11Q1, S13Q1, S19Q1
#include <stdio.h>

int m; //no. of porcesses 
int n; //no. of resources

void acceptMat(int mat[m][n]) {
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void displayMat(int mat[m][n]) {
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
}

void acceptAvailable(int mat[n]) {
	for(int i=0; i<n; i++) {
		scanf("%d", &mat[i]);
	}
}

void calculateNeed(int allocation[m][n], int max[m][n], int need[m][n]) {
	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}	
}

int safty(int allocation[m][n], int need[m][n], int available[n], int safeSequence[n]) {
	int work[n];
	//work = available resources
	for(int i=0; i<n; i++) {
		work[i] = available[i];
	}
	
	int finish[m];
	//finish initialize to 0
	for(int i=0; i<m; i++) {
		finish[i] = 0;
	}
	
	int completedProcesses = 0;
	
	//requesting resources and checking it's safty also
	while(completedProcesses < m) {
		int found = 0;
		for(int i=0; i<m; i++)	{
			if(!finish[i]) {
				int j=0;
				for(j=0; j<n; j++) {
					//checking if a process is demanding more than its need
					if(need[i][j] > work[j]) {
						break;
					}
				}
				
				//need <= work because j reached to n
				if(j == n) {
					for(int k=0; k<n; k++) {
						work[k] += allocation[i][k];
					}
					safeSequence[completedProcesses] = i;
					completedProcesses++;
					finish[i] = 1;
					found = 1;
				}
			}
		}
		if(!found) {
			return 0; //safe sequence does not exists
		}
	}
	
	return 1; //safe sequence exists
}

int main() {
	printf("Enter no. of processes: ");
	scanf("%d", &m);
	
	printf("Enter no. of resources: ");
	scanf("%d", &n);
	
	int allocation[m][n], max[m][n], need[m][n], available[n];
	printf("Enter allocation matrix:\n");
	acceptMat(allocation);
	
	printf("Enter max matrix:\n");
	acceptMat(max);
	
	printf("Enter available resources: ");
	acceptAvailable(available);
	
	calculateNeed(allocation, max, need);
	
	printf("Need Matrix is:\n");
	displayMat(need);
	
	int safeSequence[m];
	if(safty(allocation, need, available, safeSequence)) {
		printf("System is in safe sate. Safe Sequence:");
		for(int i=0; i<m; i++) {
			printf(" P%d", safeSequence[i]);
		}
		printf("\n");
	} else {
		printf("System is not safe.\n");
	}
	
	return 0;
}
