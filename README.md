# My Malloc #
Project 1 of System Architecture (CS214)

## Goals ##
Implement a version of `malloc()` and `free()` in the C programming language. The functions will store data in a 
global `memory` array. The `free()` function will also contain some warnings that the standard `free()` does not 
give, like trying to free a pointer twice, freeing a pointer that is not the head of a chunk of data, and trying 
to free an address not obtained by malloc.


## Free Implementation ##
For this implementation of free(), a simple for loop was used to go through the memory array and to determine if the given address is a valid pointer to be freed. If the given parameter is not a valid pointer given by malloc, it will print an error message accordingly (no initialization and not a valid pointer). It begins from the start of the memory + sizeof(meta) address and advances to the next meta data tag by the current chunksize amount. While going through the loop, it keeps a pointer of the previous and current meta tag to be used later in the coalesce process. 
### Coalesce upon Free ###

## Stress Testing ##
Tests 4 and 5 are of our own design, the first 3 come from 
