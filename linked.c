//linked file allocation
#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct Block {
	int blockNo;
	struct Block *next;
}Block;

typedef struct File {
	int id;
	Block *blocks;
}File;

int bitVector[MAX_BLOCKS] = {0};
File dir[MAX_BLOCKS];

void showBitVector() {
	for(int i=0; i<MAX_BLOCKS; i++) {
		printf("%d ", bitVector[i]);
	}
	printf("\n");
}

void createFile(int *p) {
	int id, blocksToAllocate;
	printf("Enter file id: ");
	scanf("%d", &id);
	
	printf("Enter block to allocate: ");
	scanf("%d", &blocksToAllocate);
	
	if(*p >= MAX_BLOCKS) {
		printf("Not enough blocks");
		return;
	}
	
	dir[*p].id = id;
	dir[*p].blocks = NULL;
	
	for(int i=0; i<blocksToAllocate; i++) {
		int blockNo;
		do {
			blockNo = rand() % MAX_BLOCKS;
		} while(bitVector[blockNo] == 1);
		
		bitVector[blockNo] = 1;
		
		Block *newBlock = (Block*)malloc(sizeof(Block));
		newBlock->blockNo = blockNo;
		newBlock->next = dir[*p].blocks;
		dir[*p].blocks = newBlock;
	}
	
	(*p)++;
}

void showDir(int p) {
	for(int i=0; i<p; i++) {
		printf("File id %d, Blocks: ", dir[i].id);
		Block *currBlock = dir[i].blocks;
		while(currBlock != NULL) {
			printf("%d ", currBlock->blockNo);
			currBlock = currBlock->next;
		}
		printf("\n");
	}
}

void deleteFile(int *p) {
	int id;
	printf("Enter the file id to delete: ");
	scanf("%d", &id);
	
	int idx = -1;
	for(int i=0; i<*p; i++) {
		if(dir[i].id == id) {
			idx = i;
			break;
		}
	}
	
	if(idx != -1) {
		Block *currBlock = dir[idx].blocks;
		while(currBlock != NULL) {
			int blockNo = currBlock->blockNo;
			bitVector[blockNo] = 0;
			Block *temp = currBlock;
			currBlock = currBlock->next;
			free(temp);
		}
		
		for(int i=idx; i<*p-1; i++) {
			dir[i] = dir[i+1];
		}
		
		(*p)--;
		printf("File id %d deleted successfully.\n", id);
	} else {
		printf("File not found.\n");
	}
}

int main() {
	int ch, p=0;
	
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
			case 2: createFile(&p);
				break;
			case 3: showDir(p);
				break;
			case 4: deleteFile(&p);
				break;
		}
	} while(ch != 5);
	
	return 0;
}
