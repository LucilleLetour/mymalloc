# My Malloc #
Project 1 of System Architecture (CS214)

## Goals ##
Implement a version of `malloc()` and `free()` in the C programming language. The functions will store data in a 
global `memory` array. The `free()` function will also contain some warnings that the standard `free()` does not 
give, like trying to free a pointer twice, freeing a pointer that is not the head of a chunk of data, and trying 
to free an address not obtained by malloc.




## Free Implementation ##
For this implementation of `free()`, a simple for loop was used to go through the memory array and determine if the given address is a valid pointer to be freed. If the given parameter is not a valid pointer given by malloc, it will print an error message accordingly. The loop begins from the start of the memory + sizeof(meta) address and advances to the next meta data tag by the current chunk size amount. While going through the loop, it keeps a pointer of the previous, current, and next meta tags to be used later in the coalesce process. 

### Coalesce upon Free ###
After checking that it is a valid pointer to be freed, free will attempt to coalesce the current meta tag with the previous and next tag. In other words, the only possible areas that could be combined with the current chunk area (which are the spaces in front and behind the memory chunk) are taken into consideration and do not need to be considered to coalesce again. This approach ensures that we take care of all free cases instead of attempting to coalesce in malloc which may have multiple coalesce procedures. 

## Stress Testing ##
Tests 4 and 5 are of our own design, the first 3 come from assignment's required testing procedure
### Test1 ###
`malloc()` and immediately `free()` a 1-byte chunk, 120 times.
### Test2 ###
Use `malloc()` to get 120 1-byte chunks, storing the pointers in an array, then use `free()` to deallocate the chunks.
### Test3 ###
Allocating a 1-byte chunk and storing the pointer in an array
### Test4 ###
Allocating random size byte chunks until failure and freeing the random size byte chunks randomly
### Test5 ###
Allocating a n-byte chunks until failure and freeing every other pointer where n = 0 to MEMSIZE (4096)
