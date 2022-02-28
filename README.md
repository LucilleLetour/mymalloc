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
For this implementation of `free()`, a simple for loop was used to go through the memory array and determine if the given address is a valid pointer to be freed. If the given parameter is not a valid pointer given by malloc, it will print an error message accordingly. The loop begins from the start of the memory + sizeof(meta) address and advances to the next meta data tag by the current chunk size amount. While going through the loop, it keeps a pointer of the previous, current, and next meta tags to be used later in the coalesce process. In terms of the error message, it will print out in this fashion: "ERROR -type of error at- FILE, LINE". The erros it will detect are invalid pointers, null pointers, or possible double free pointers.

### Coalesce upon Free ###
After checking that it is a valid pointer to be freed, free will attempt to coalesce the current meta tag with the previous and next tag. In other words, the only possible areas that could be combined with the current chunk area (which are the spaces in front and behind the memory chunk) are taken into consideration and do not need to be considered to coalesce again. This approach ensures that we take care of all free cases instead of attempting to coalesce in malloc which may have multiple coalesce procedures.

### Test plan for Free during development###
During the development of `free()`, several additional programs were created to detect if it was actually freeing the chunk and determining if it was coalescing properly. Within `main2()` in mymalloc.c (orignally named `main()` to test during the development phase), `memdump()` was utilized to print out the entire memory space upon each `malloc()` and `free()` calls. `memdump()` will go through the memory char array and individually print out each index. Additionally, during testing, a MEMSIZE of 32 was used to keep the print out as brief as possible while providing a great amount of output for debugging. After each print out, the output was throughly reviewed to identify if it was performing as properly. When certain unforseen errors did arise, a replicate of the problem was tested and the functions were meticulously debugged. For the test plan of deteremining if `free()` was performing correctly, a pointer ahead of memory, before memory, offset from valid metatag, and NULL were individually tested to determine if the memory stayed consistent with the corresponding calls. For coalesce, multiple pointer orders were tested to see the change in chunk size for the metatag. For example, if 3 memory chunks were in order, a free in the order of (1,2,3), (2,1,3), (2,3,1), (1,3,2), (3,1,2), and (3,2,1) were tested for proper coalesce procedures. During this process, invalid pointesr were mixed in between the orders to test inconsistency but the functions reported the corresponding error messages and did not interfere with memory. Finally, normal free calls with the given malloc pointers were tested by using `memdump()` and checking the is_reserved tag.

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
