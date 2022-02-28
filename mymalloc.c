#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#pragma pack(1)

//#define MEMSIZE 4096

#define check(p) if(p == NULL) {\
printf("Null pointer at " __FILE__ ":%d\n", __LINE__); \
exit(EXIT_FAILURE);\
}

static char memory[MEMSIZE];

typedef enum { false, true } bool;

typedef struct meta {
	char is_reserved;
	unsigned short chunk_size;
} meta;

int metasize() {
	return sizeof(meta);
}

void memdump() 
{
	for(int i = 0; i < MEMSIZE; i++) {
		printf("%d\n", memory[i]);
	}
	printf("--------\n");
}

void* mymalloc(size_t p, char* file, int line) {
	//printf(__FILE__ " at line: %d\n", __LINE__);
	// Goal: find first available free chunk with adequate size
	int curLoc = 0;
	meta* metaBlock = (meta*)&memory[curLoc];
	if(metaBlock->chunk_size == 0) {
		//This should only happened on an uninitialized memory array, intializes arr with a Meta tag defining the entire space as free
		metaBlock->is_reserved = 0;
		//printf("%d\n", sizeof(meta));
		//printf("%d\n", sizeof(char));
		//printf("%d\n", sizeof(unsigned short));
		metaBlock->chunk_size = MEMSIZE - sizeof(meta);
		//printf("memory initialized\n");
	}

	//memdump();

	while(curLoc < MEMSIZE) {
		metaBlock = (meta*)&memory[curLoc];
		if(!metaBlock->is_reserved && metaBlock->chunk_size >= p) {
			// We have enough space in this free chunk to create a malloc'd chunk
			if(metaBlock->chunk_size < p + sizeof(meta) + sizeof(char)) {
				// The chunk does not have enough room to fit both our data AND another chunk meta tag and at least a char
				metaBlock->is_reserved = true;
			} else {
				// We have enough spcae for the requested chunk and another (free, for now) chunk
				meta *metaBlock2 = (meta*)&memory[curLoc + sizeof(meta) + p];
				metaBlock2->is_reserved = false;
				metaBlock2->chunk_size = metaBlock->chunk_size - p - sizeof(meta);
				metaBlock->is_reserved = true;
				metaBlock->chunk_size = p;
			}
			return &memory[curLoc] + sizeof(meta);
		} else {
			//TODO: Check if this overflows over MEMSIZE
			curLoc += sizeof(meta) + metaBlock->chunk_size;
		}
	}
	printf("ERROR: No free memory at %s:%d\n", file, line);
	return NULL;
}

void myfree(void* p, char* file, int line)
{
	//check for NULL pointer
	if(p==NULL)
	{
		printf("ERROR: Tried to free a null pointer at %s:%d\n", file, line);
		return;
	}
	//set up meta pointers
	meta* metaPrev = NULL;
	meta* metaCurr = (meta*)&memory;
	//Check if memory is not initialized 
	if(metaCurr->chunk_size == 0)
	{
		printf("ERROR: Nothing has been malloced at %s:%d\n", file, line);
		return;
	}
	//for loop through the entire memory and advance by the chunk size
	for(;metaCurr < (meta*)&memory[MEMSIZE]; metaCurr = (meta*)((char*)metaCurr + sizeof(meta) + metaCurr->chunk_size))
	{
		void* addressCheking = (void*)((char*)metaCurr + sizeof(meta));
		//printf("current meta address: %u \n", metaCurr);
		//printf("size of meta: %u \n", sizeof(meta));
		//printf("checking address in loop to p: %u, %u\n", addressCheking, p);
		//printf("addressing chekcing %u, pointer given %u\n", addressCheking, p);

		//Check if address given is valid pointer
		if(addressCheking == p)
		{	
			//Check if that pointer is already freed
			if(metaCurr->is_reserved==false)
			{
				printf("ERROR: Possible double free at %s:%d\n", file, line);
				return;
			}
			//printf("found location\n");
			metaCurr->is_reserved = false;
			meta* metaNext = (meta*)((char*)metaCurr + sizeof(meta) + metaCurr->chunk_size);

			//coalesce with previous meta tag
			if(metaPrev != NULL && metaPrev->is_reserved == false)
			{
				metaPrev->chunk_size += sizeof(meta) + metaCurr->chunk_size;
			}
			//coalesce with mext meta tag
			if(metaNext < (meta*)&memory[MEMSIZE])
			{	
				if(metaPrev != NULL && metaPrev->is_reserved==false && metaNext->is_reserved==false)
				{
					metaPrev->chunk_size += sizeof(meta) + metaNext->chunk_size;
				}
				else if(metaNext->is_reserved==false)
				{
					metaCurr->chunk_size += sizeof(meta) + metaNext->chunk_size;
				}
			}
			return;
		}
		else if(addressCheking > p)
		{
			break;
		}
		//advance prev pointer to current
		metaPrev = metaCurr;
	}
	//not a valid pointer given by malloc
	printf("ERROR: Not a valid pointer given by malloc at %s:%d\n", file, line);
}


int main2(int argc, char* argv) 
{
	// unsigned int* memStart = memory;
	// free(memStart);
	// char* short_str = malloc(sizeof(char) * 6);
	// short_str[0] = 'H';
	// short_str[1] = 'e';
	// short_str[2] = 'l';
	// short_str[3] = 'l';
	// short_str[4] = 'o';
	// short_str[5] = '\0';
	// printf("===MEMDUMPING===\n");
	// memdump();
	// printf("freeing: %u \n",short_str);
	// free(short_str);
	// memdump();
	// return EXIT_SUCCESS;
}
