# My Malloc
Project 1 of System Architecture (CS214)

## Goals
Implement a version of `malloc()` and `free()` in the C programming language. The functions will store data in a 
global `memory` array. The `free()` function will also contain some warnings that the standard `free()` does not 
give, like trying to free a pointer twice, freeing a pointer that is not the head of a chunk of data, and trying 
to free an address not obtained by malloc.
