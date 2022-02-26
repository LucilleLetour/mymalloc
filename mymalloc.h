void* mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);
void memdump();
int metasize();

//extern const int MEMSIZE;

#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)
#define MEMSIZE 4096
