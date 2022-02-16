mymalloc: mymalloc.c memgrind.c
	gcc mymalloc.c memgrind.c -o mymalloc.o

memgrind: memgrind.c
	gcc memgrind.c -o memgrind.o

.PHONY: clean
clean:
	-rm *.o $(objects)
