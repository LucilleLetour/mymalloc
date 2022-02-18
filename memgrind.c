#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//#define USE_STD_MALLOC

#ifndef USE_STD_MALLOC
	#include "mymalloc.h"
#endif

#define TEST_ITERATIONS 50
#define MEASURE_MICRO_SEC(x) ({clock_t start = clock(); x(); clock_t diff = clock() - start; diff * 1000000 / CLOCKS_PER_SEC;})
#define AVG_TIME(x) ({double tot = 0; for(int i = 0; i < TEST_ITERATIONS; i++) { tot += MEASURE_MICRO_SEC(x); } tot / TEST_ITERATIONS;})


//#define MEASURE_MSEC(x) ({start = clock(); x; diff = clock() - start; diff * 1000 / CLOCKS_PER_SEC;})

// Allocate and immediately free 120 1-byte chunks
void test1() {
	for(int i = 0; i < 120; i++) {
		char *n = (char*) malloc(sizeof(char));
		free(n);
	}
}

// Allocate 120 1-byte chunks and store pointer in array, then free all chunks
void test2() {
	char *ptrs[120];

	for(int i = 0; i < 120; i++) {
		ptrs[i] = (char*)malloc(sizeof(char));
		printf("%d\n", i);
	}

	for(int i = 0; i < 120; i++) {
		free(ptrs[i]);
	}
}

// Randomly choose between allocating a 1-byte chunk or freeing one (if possible) 120 times
void test3() {
	int numAllocated = 0;
	char *ptrs[120];
	for(int i = 0; i < 120; i++) {
		if(rand() % 2) {
			ptrs[numAllocated++] = (char*)malloc(sizeof(char));
		} else {
			if(numAllocated > 0) {
				free(ptrs[--numAllocated]);
			}
		}
	}
}

int empty(char* ptrs[],int index)
{
	for(int i =0; i<index;i++)
	{
		if(ptrs[i]!=0)
		{
			return 1;
		}
	}
	return 0;
}

// Custom test #1
void test4() 
{
	char* ptrs[4096];
	int index = 0;
	int length = rand() % 30 +1;
	char* pointer = (char*)malloc(length);
	while(pointer!=NULL)
	{
		ptrs[index++] == pointer;
		length = rand() % 30 +1;
		pointer = (char*)malloc(length);
	}
	pointer = (char*)malloc(sizeof(char));
	while(pointer!=NULL)
	{
		ptrs[index++] == pointer;
		pointer = (char*)malloc(sizeof(char));
	}
	while(empty(ptrs, index)==1)
	{
		length = rand() % index;
		if(ptrs[length]==NULL)
		{
			continue;
		}
		free(ptrs[length]);
		ptrs[length]==NULL;
	}
	pointer = (char*)malloc(4096-3);
	if(pointer == NULL)
	{
		printf("FAILED");
	}
}



// Custom test #2
void test5() 
{
	
}

int main(int argc, char* argv) {
	printf("Test 1 average: %f μs\n", AVG_TIME(test1));
	printf("Test 2 average: %f μs\n", AVG_TIME(test2));
	printf("Test 3 average: %f μs\n", AVG_TIME(test3));
	printf("Test 4 average: %f μs\n", AVG_TIME(test4));
	printf("Test 5 average: %f μs\n", AVG_TIME(test5));
}
