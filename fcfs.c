//S1Q1, S9Q2, S17Q2, S21Q1

#include <stdio.h>
#include <math.h>

void fcfs(int arr[], int n, int head) {
	int seek_cnt = 0;
	int curr_track, dist;
	
	for(int i=0; i<n; i++) {
		curr_track = arr[i]; 
		// absolute distance
		dist = fabs(head - curr_track);
		// increase the total count
		seek_cnt += dist; 
		// update new head
		head = curr_track;
	}
	
	printf("Total no. of seek oprations: %d\n", seek_cnt);
	
	printf("Seek Sequence is:\n");
	for(int i=0; i<n; i++)
		printf("%d\n", arr[i]);
}

int main() {
	int arr[100], n, head;
	
	printf("Enter request array size: ");
	scanf("%d", &n);
	
	printf("Enter request array:\n");
	for(int i=0; i<n; i++)
		scanf("%d", &arr[i]);
		
	printf("Enter initial head position: ");
	scanf("%d", &head);
	
	fcfs(arr, n, head);
	
	return 0;
}

