//S8Q2, S12Q2, S14Q2
#include <stdio.h>
#include <math.h>

void claculate_diff(int arr[], int n, int head, int diff[][2]) {
	for(int i=0; i<=n; i++)
		diff[i][0] = fabs(head - arr[i]);
}

//find unaccessed track which is at
//minimum distance from head
int find_min(int diff[][2], int n) {
	int idx = -1;
	int min = 1e7;
	
	for(int i=0; i<n; i++) {
		if(!diff[i][1] && min > diff[i][0]) {
			min = diff[i][0];
			idx = i;
		}
	}
	
	return idx;
}

void sstf(int arr[], int n, int head) {
	if(n == 0)
		return;
		
	int diff[n][2];
	
    // Initialize diff array elements
    for (int i = 0; i < n; i++) {
        diff[i][0] = 0;
        diff[i][1] = 0;
    }
	int seek_cnt = 0;
	int seek_seq[n+1];
	for(int i=0; i<=n; i++)
		seek_seq[i] = 0;
	
	for(int i=0; i<n; i++) {
		seek_seq[i] = head;
		claculate_diff(arr, n, head, diff);
		int idx = find_min(diff, n);
		diff[idx][1] = 1;
		// increase the total count
		seek_cnt += diff[idx][0];
		// update new head
		head = arr[idx];
	}
	
	seek_seq[n] = head;
	printf("Total no. of seek oprations: %d\n", seek_cnt);
	
	printf("Seek Sequence is:\n");
	for(int i=0; i<=n; i++)
		printf("%d\n", seek_seq[i]);
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
	
	sstf(arr, n, head);
	
	return 0;
}

