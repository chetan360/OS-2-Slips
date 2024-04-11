//S6Q2, S10Q2, S15Q2, S19Q2
#include <stdio.h>
#include <math.h>

int disk_size = 200;

void bsort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            if(arr[j+1]<arr[j]) {
                int t = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = t;
            }
        }
    }
}

void cscan(int arr[], int n, int head, char dir) {
	int seek_cnt = 0;
	int dist, curr_track;
	int left[100], right[100], seek_seq[100];
	int l_cnt=0, r_cnt=0, s_cnt=0;
	
	left[l_cnt++] = 0;
	right[r_cnt++] = disk_size - 1;
	
	for(int i=0; i<n; i++) {
		if(arr[i] < head)
			left[l_cnt++] = arr[i];
		if(arr[i] > head)
			right[r_cnt++] = arr[i];
	}
	
	bsort(left, l_cnt);
	bsort(right, r_cnt);
	
	
	//for right direction:
	//run left loop first and then
	//right in reverse index
	
	//right loop
	for(int i=0; i<r_cnt; i++) {
		curr_track = right[i];
		seek_seq[s_cnt++] = curr_track;
		dist = fabs(curr_track - head);
		seek_cnt += dist;
		head = curr_track;
	}
	
	//lrft loop
	for(int i=0; i<l_cnt; i++) {
		curr_track = left[i];
		seek_seq[s_cnt++] = curr_track;
		dist = fabs(curr_track - head);
		seek_cnt += dist;
		head = curr_track;
	}
	
		
	printf("Total no. of seek oprations: %d\n", seek_cnt);
	
	printf("Seek Sequence is:\n");
	for(int i=0; i<s_cnt; i++)
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
	
	cscan(arr, n, head, 'r');
	
	return 0;
}

