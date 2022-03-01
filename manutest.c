#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

// A collection of various tests used to manually test the functioning of `malloc()` and `free()`
int main(int argc, char* argv) {
	char* short_str = malloc(sizeof(char) * 6);
	short_str[0] = 'H';
	short_str[1] = 'e';
	short_str[2] = 'l';
	short_str[3] = 'l';
	short_str[4] = 'o';
	short_str[5] = '\0';
	//printf("===MEMDUMPING===\n");
	//memdump();
	printf("freeing: %u \n",short_str);
	free(short_str);
	//memdump();
	return EXIT_SUCCESS;

	// char* short_str = malloc(sizeof(char) * 6);
	// printf("first %u \n", short_str);
	// short_str[0] = '1';
	// short_str[1] = '2';
	// short_str[2] = '3';
	// short_str[3] = '4';
	// short_str[4] = '5';
	// short_str[5] = '6';
	// memdump();
	// printf("____\n");

	// char* short_str2 = malloc(sizeof(char) * 6);
	// printf("second %u \n", short_str2);
	// short_str2[0] = 'a';
	// short_str2[1] = 'b';
	// short_str2[2] = 'c';
	// short_str2[3] = 'd';
	// short_str2[4] = 'e';
	// short_str2[5] = 'f';
	// memdump();
	// printf("____\n");


	// char* short_str3 = malloc(sizeof(char) * 5);
	// printf("third %u \n", short_str3);
	// short_str3[0] = 't';
	// short_str3[1] = 'u';
	// short_str3[2] = 'v';
	// short_str3[3] = 'w';
	// short_str3[4] = 'x';
	// memdump();
	// printf("____\n");

	// char* short_str4 = malloc(sizeof(char) * 3);
	// if(short_str4!=NULL)
	// {
	// printf("fourth %u \n", short_str4);
	// short_str4[0] = 'a';
	// short_str4[1] = 'b';
	// short_str4[2] = 'c';
	// }

	// memdump();
	// printf("____\n");

	// printf("third freed\n");
	// free(short_str3);
	// memdump();
	// printf("____\n");
	// printf("secind freed\n");
	// free(short_str2);
	// memdump();
	// printf("____\n");
	// printf("first freed\n");
	// free(short_str);
	// memdump();
	// printf("____\n");
	// printf("fourth freed\n");
	// free(short_str4);
	// memdump();
	// printf("____\n");


	// printf("first freed again\n");
	// free(short_str);
	// memdump();
	// printf("____\n");
}
