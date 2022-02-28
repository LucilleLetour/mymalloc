# My Malloc #
Project 1 of System Programming (CS214)

## Goals ##
Implement a version of `malloc()` and `free()` in the C programming language. The functions will store data in a global `memory` array. The `free()` function will also contain some warnings that the standard `free()` does not give, like trying to free a pointer twice, freeing a pointer that is not the head of a chunk of data, and trying to free an address not obtained by malloc.


## Meta Tag Implementation ##
In order to maximize the amount of memory used on the memory array, the smallest amount of data types were used for the meta tag. Char data type was used to determine if a meta tag for a chunk was used or freed. Short data type was used to record how many bytes were allocated for the meta tag chunk. Since short can cover up to index 32,767 (or 65,535 if unsigned), it is enough for 4096 or any MEMSIZE other less than short. In addition, the struct was packed to 1 byte alignment in order to minimize the memory footprint and leave more memory for the actual user data. 

## Malloc Implementation ##
For `malloc()`, the main structure was a simple linear search for a memory chunk that contained enough bytes to house the user data. Before the loop, the input was checked (user cannot request 0 or less bytes) and the memory was checked to see if it started with a meta tag of chunk size 0. Each byte of the memory is initialized to 0 on the program's start (a requirement of this implementation), so by treating the first 3 bytes as a meta tag we would get that the chunk size is 0. This should never be the case, as that would imply that there is a meta tag pointing to no data and the pointer that matches that tag would be the next meta tag; It would be a mess. Thus, we take this opportunity to make a meta tag that essentially declares the entire memory as free.

After this initialization, we start a search for an adequate chunk of memory for the user. If we come across one that is not free or does not have enough space, we go to the next. If we come across memory that is free and has enough space, we mark it reserved and return a pointer to the start to the user. An edge case of this is if a chunk contains, say, 3 bytes and the user requested 2. This would mean there is one byte of additional space - not enough for a meta tag and data afterwards. In this case we mark the whole chunk as reserved and take the hit of a few "lost" bytes. If there is adequate space though (4 bytes minimum, 3 for header and a minimum 1 for data), we create a new meta tag after the amount of data the user requested. If at any point we exceed the bounds of the memory, we say we cannot fulfill the user's request and return a null pointer and give an error message.

## Free Implementation ##
For this implementation of `free()`, a simple for loop was used to go through the memory array and determine if the given address is a valid pointer to be freed. If the given parameter is not a valid pointer given by malloc, it will print an error message accordingly. The loop begins from the start of the memory + sizeof(meta) address and advances to the next meta data tag by the current chunk size amount. While going through the loop, it keeps a pointer of the previous, current, and next meta tags to be used later in the coalesce process. In terms of the error message, it will say either: invalid pointer, null pointer, or possible double free depending on the pointer.

### Coalesce upon Free ###
After checking that it is a valid pointer to be freed, free will attempt to coalesce the current meta tag with the previous and next tag. In other words, the only possible areas that could be combined with the current chunk area (which are the spaces in front and behind the memory chunk) are taken into consideration and do not need to be considered to coalesce again. This approach ensures that we take care of all free cases instead of attempting to coalesce in malloc which may have multiple coalesce procedures.

## Stress Testing ##
Tests 4 and 5 are of our own design, the first 3 come from assignment's required testing procedure
### Test1 ###
`malloc()` and immediately `free()` a 1-byte chunk, 120 times.
### Test2 ###
Use `malloc()` to get 120 1-byte chunks, storing the pointers in an array, then use `free()` to deallocate the chunks.
### Test3 ###
Randomly allocate a 1-byte chunk and store the pointer in an array or free a recent chunk 120 times
### Test4 ###
Allocating random size byte chunks until failure (running out of availible memory) and freeing the chunks at even then odd location to test coalesce.
### Test5 ###
Allocating a maximum amount of 1-byte chunks and randomly freeing until the entire memory is empty
