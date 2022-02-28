#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//#define USE_STD_MALLOC // Define to test the test cases using malloc() and free() from the standard library

#ifndef USE_STD_MALLOC
	#include "mymalloc.h"
#else
	#define MEMSIZE 4096
	#define METASIZE 3
#endif

#define TEST_ITERATIONS 50
#define MEASURE_MICRO_SEC(x) ({clock_t start = clock(); x(); clock_t diff = clock() - start; diff * 1000000 / CLOCKS_PER_SEC;})
#define AVG_TIME(x) ({double tot = 0; for(int i = 0; i < TEST_ITERATIONS; i++) { tot += MEASURE_MICRO_SEC(x); } tot / TEST_ITERATIONS;})

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
		//printf("%d\n", i);
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
	for(int i = 0; i < numAllocated; i++) 
	{
		free(ptrs[i]);
	}
}



// Custom test #1 - Outlined in README
void test4() {
	char* ptrs[MEMSIZE];
	int ptridx = -1;
	int memidx = 0;
	while(memidx + METASIZE + 10 < MEMSIZE) {
		int len = rand() % 10 + 1;
		ptrs[++ptridx] = (char*)malloc(len);
		memidx += METASIZE + len;
	}

	while(memidx + METASIZE + sizeof(char) < MEMSIZE) {
		ptrs[++ptridx] = (char*)malloc(sizeof(char));
		memidx += METASIZE + sizeof(char);
	}

	for(int i = 0; i <= ptridx; i += 2) {
		free(ptrs[i]);
	}

	for(int i = 1; i <= ptridx; i += 2) {
		free(ptrs[i]);
	}

	void* pointer = malloc(MEMSIZE - METASIZE);
	if(pointer == NULL) {
		printf("FAILED\n");
	}
	free(pointer);
}

// Shuffles a list
void shuffle(char* list[], int len) {
	for (int i = 0; i < len - 1; ++i) {
    	int j = rand() % (len - i) + i;
	    char* temp = list[i];
    	list[i] = list[j];
    	list[j] = temp;
	}
}

// Custom test #2 - Outlined in README
void test5() {
	int count = 0;
	int index = 0;
	char* ptrs[4096];
	while(count+4<=4096)
	{
		char* pointer = (char*)malloc(sizeof(char));
		count+=4;
		ptrs[index] = pointer;
		index++;
	}
	shuffle(ptrs, index);
	for(int i = 0; i < index; i++) {
		free(ptrs[i]);
	}


	char* temp = (char*)malloc(4096 - 3);
	if(temp == NULL) {
		printf("FAILED\n");
	}
	free(temp);
}

// Runs each test a number of times and averages the run time across them
int main(int argc, char* argv) {
	time_t t;
	srand(time(&t)); // Initializes the rand() function

	printf("Test 1 average: %f μs\n", AVG_TIME(test1));
	printf("Test 2 average: %f μs\n", AVG_TIME(test2));
	printf("Test 3 average: %f μs\n", AVG_TIME(test3));
	printf("Test 4 average: %f μs\n", AVG_TIME(test4));
	printf("Test 5 average: %f μs\n", AVG_TIME(test5));
}
