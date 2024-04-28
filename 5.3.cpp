#include <stdio.h> 
#include <stdlib.h> 
// Define a structure for a block of free space 
typedef struct FreeBlock { 
int start; 
int size; 
struct FreeBlock* next; 
} FreeBlock; 
// Function to initialize a new free block 
FreeBlock* createBlock(int start, int size) { 
FreeBlock* block = (FreeBlock*)malloc(sizeof(FreeBlock)); 
if (block == NULL) { 
printf("Memory allocation failed!\n"); 
exit(1); 
} 
block->start = start; 
block->size = size; 
block->next = NULL; 
return block; 
} 
// Function to display the free blocks 
void displayBlocks(FreeBlock* head) { 
printf("Free Blocks:\n"); 
while (head != NULL) { 
printf("Start: %d, Size: %d\n", head->start, head->size); 
head = head->next; 
} 

printf("\n"); 
} 
// Function to allocate disk space 
int allocateSpace(FreeBlock** head, int size) { 
if (*head == NULL || (*head)->size < size) 
return -1; // Not enough space available 
int allocatedStart = (*head)->start; 
(*head)->start += size; 
(*head)->size -= size; 
if ((*head)->size == 0) { 
FreeBlock* temp = *head; 
*head = (*head)->next; 
free(temp); 
} 
return allocatedStart; 
} 
// Function to deallocate disk space 
void deallocateSpace(FreeBlock** head, int start, int size) { 
FreeBlock* newBlock = createBlock(start, size); 
newBlock->next = *head; 
*head = newBlock; 
} 
// Function to find the position to insert a new free block 

// Returns the predecessor of the position where the new block should be inserted 
FreeBlock* findInsertionPosition(FreeBlock* head, int start) { 
FreeBlock* prev = NULL; 
while (head != NULL && head->start < start) { 
prev = head; 
head = head->next; 
} 
return prev; 
} 
// Function to merge adjacent free blocks 
void mergeAdjacentBlocks(FreeBlock* head) { 
while (head != NULL && head->next != NULL) { 
if (head->start + head->size == head->next->start) { 
head->size += head->next->size; 
FreeBlock* temp = head->next; 
head->next = head->next->next; 
free(temp); 
} else { 
head = head->next; 
} 
} 
} 
// Function to insert a new free block 
void insertFreeBlock(FreeBlock** head, FreeBlock* newBlock) { 
FreeBlock* prev = findInsertionPosition(*head, newBlock->start); 
if (prev == NULL) { 
newBlock->next = *head; 
*head = newBlock; 

} else { 
 
newBlock->next = prev->next; 
prev->next = newBlock; 
} 
mergeAdjacentBlocks(*head); 
} 
int main() { 
int diskSize; 
printf("Enter the initial size of the disk space: "); 
scanf("%d", &diskSize); 
FreeBlock* freeList = createBlock(0, diskSize); 
displayBlocks(freeList); 
int allocateSize; 
printf("Enter the size to allocate: "); 
scanf("%d", &allocateSize); 
int allocatedSpace = allocateSpace(&freeList, allocateSize); 
if (allocatedSpace != -1) 
printf("Allocated space starting at %d\n", allocatedSpace); 
else 
printf("Not enough space available for allocation\n"); 
displayBlocks(freeList); 
int deallocateSize; 
printf("Enter the size to deallocate: "); 
 
scanf("%d", &deallocateSize); 
deallocateSpace(&freeList, allocatedSpace, deallocateSize); 
printf("Deallocated space starting at %d\n", allocatedSpace); 
displayBlocks(freeList); 
return 0; 
} 

