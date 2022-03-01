mymalloc: mymalloc.c memgrind.c
	gcc mymalloc.c memgrind.c -o mymalloc.o

memgrind: mymalloc.c memgrind.c
	gcc mymalloc.c memgrind.c -o memgrind.o

manutest: mymalloc.c manutest.c
	gcc mymalloc.c manutest.c -o manutest.o

.PHONY: clean
clean:
	-rm *.o $(objects)
