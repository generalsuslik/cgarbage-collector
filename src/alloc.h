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
};

#define META_SIZE sizeof(struct block_meta)

struct block_meta *find_free_block(struct block_meta **last, size_t size);
struct block_meta *request_space(struct block_meta *last, size_t size);
void *m_alloc(size_t size);
void m_free(void *ptr);
void print_blocks();


