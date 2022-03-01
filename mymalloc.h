void* mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)
#define MEMSIZE 4096
// Number of bytes the meta struct uses, in here for testing purposes: mymalloc.c uses `sizeof(meta)`
#define METASIZE 3
