//contigious file allocation

#include <stdio.h>

#define MAX_BLOCKS 100

int bitVector[MAX_BLOCKS] = {0};
int dir[MAX_BLOCKS][2] = {0};
int dirSize = 0;

int showBitVector() {
	for(int i=0; i<MAX_BLOCKS; i++) {
		printf("%d ", bitVector[i]);
	}
	printf("\n");
}

int findFreeBlocks(int blocksToAllocate) {
	int cnt = 0;
	for(int i=0; i<MAX_BLOCKS; i++) {
		if(bitVector[i] == 0) {
			cnt++;
			if(cnt == blocksToAllocate) {
				return i - cnt + 1;
			}
		} else {
			cnt = 0;
		}
	}
	
	return -1;
}

void createFile() {
	int blocksToAllocate;
	
	printf("Enter blocks to allocate: ");
	scanf("%d", &blocksToAllocate);
	
	int startBlock = findFreeBlocks(blocksToAllocate);
	if(startBlock == -1) {
		printf("Not enough free blocks..\n");
		return;
	}
	
	for(int i=startBlock; i<startBlock+blocksToAllocate; i++) {
		bitVector[i] = 1; 
	}
	
	dir[dirSize][0] = startBlock;
	dir[dirSize++][1] = blocksToAllocate;
	printf("File id %d created successfully.\n", dirSize);
}

void showDir() {
	for(int i=0; i<dirSize; i++) {
		printf("File id: %d, Start block: %d, Block allocated: %d\n", i+1, dir[i][0], dir[i][1]);
	}
}

void deleteFile() {
	int id;
	printf("Enter file id to delete: ");
	scanf("%d", &id);
	
	if(id <= 0 || id > dirSize) {
		printf("Invalid file id");
		return;
	}
	
	int startBlock = dir[id-1][0];
	int blockAllocated = dir[id-1][1];
	
	for(int i=startBlock; i<startBlock+blockAllocated; i++) {
		bitVector[i] = 0;
	}
	
	dir[id-1][0] = -1;
	dir[id-1][1] = -1;
	
	printf("File id %d deleted successfully.\n", id);
}

int main() {
	int ch;
	
	do {
		printf("\n\nMenu\n");
		printf("1. Show bit vector.\n");
		printf("2. Create file.\n");
		printf("3. Show dir.\n");
		printf("4. Delete file.\n");
		printf("5. Exit.\n\n");
		
		printf("Enter your choise: ");
		scanf("%d", &ch);
		
		switch(ch) {
			case 1: showBitVector();
				break;
			case 2: createFile();
				break;
			case 3: showDir();
				break;
			case 4: deleteFile();
				break;
		}
	} while(ch != 5);
}
