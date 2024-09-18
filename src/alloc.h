#include <assert.h>
#include <string.h>
#include <unistd.h>

/*
 * struct representing
 * block of bytes in memory
 */
struct block_meta {
	size_t size;
	struct block_meta *next;	
	int free;
};

struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta *last, size_t size);
void *m_alloc(size_t size);
void split_block(struct block_meta *block, size_t required_size);
struct block_meta *get_block_ptr(void *ptr);
void m_free(void *ptr);
void merge_blocks(struct block_meta *start_block);
void *m_realloc(void *ptr, size_t size);
void *m_calloc(size_t nelem, size_t elsize);

