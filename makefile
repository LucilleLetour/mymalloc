all: mymalloc.c memgrind.c
	gcc mymalloc.c -o mymalloc.o
	gcc memgrind.c -o memgrind.o
	gcc manutest.c -o manutest.o

memgrind: memgrind.c
	gcc memgrind.c -o memgrind.o

mymalloc: mymalloc.c
	gcc memgrind.c -o memgrind.o

mymalloc: manutest.c
	gcc manutest.c -o manutest.o

.PHONY: clean
clean:
	-rm *.o $(objects)
