//S8Q2, S12Q2, S14Q2
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define N 8
#define DISK_SIZE 200

void calculateDiff(int arr[], int head, int diff[][2]) {
	for(int i=0; i<N; i++) {
		diff[i][0] = fabs(head - arr[i]);
	}
}

int findMin(int diff[][2]) {
	int idx = -1;
	int min = INT_MAX;
	for(int i=0; i<N; i++) {
		if(!diff[i][1] && diff[i][0] < min) {
			min = diff[i][0];
			idx = i;
		}
	}
	
	return idx;
}

void sstf(int arr[], int head) {
	int seekCnt = 0, seekSeq[N];
	
	int diff[N][2];
	for(int i=0; i<N; i++) {
		diff[i][1] = 0;
	}
	
	for(int i=0; i<N; i++) {
		calculateDiff(arr, head, diff);
		int idx = findMin(diff);
		diff[idx][1] = 1;
		seekCnt += diff[idx][0];
		head = arr[idx];
		seekSeq[i] = head;
	}
	
	printf("Total no. seek oprations: %d\n", seekCnt);
	
	printf("Seek sequence:\n");
	for(int i=0; i<N; i++) {
		printf("%d\n", seekSeq[i]);
	}
}

int main() {
	int arr[N], head;
	
	printf("Enter request arr:\n");
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
	}
	
	printf("Enter head position: ");
	scanf("%d", &head);
	
	sstf(arr, head);
	
	return 0;
}

