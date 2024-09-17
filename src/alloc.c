#include <assert.h>
#include <unistd>

/*
 * struct representing 
 * block of bytes in memory
 * ... i guess
 */
struct block_meta {
	size_t size;
	struct block_meta *next;
	int    free;
};

#define META_SIZE sizeof(struct block_meta)

void *global_base = NULL;

/*
 * searches for already allocated memory block to use it
 * by iterating over the linked list of already created blocks
 */
struct block_meta *find_free_block(struct block_meta **last, size_t size) 
{
	struct block_meta *curr = global_base;
	while (curr && !(curr->free && curr->size >= size)) 
	{
		*last = curr;
		curr = curr->next;
	}

	return curr;
}

/*
 * requests free space from OS
 * in case find_free_block failed and there is 
 * no created block that can be used
 */
struct block_meta *request_space(struct block_meta *last, size_t size) 
{
	struct block_meta *block;
	block = sbrk(0); // used to find the current location of program break (end of process's data segment)
	void *request = sbrk(size + META_SIZE);
	assert((void *)block == request);
	if (request == (void *) -1) 
	{
		return NULL;
	}

	if (last)
	{
		last->next = block;
	}

	block->size = size;
	block->next = NULL;
	block->free = 0;
	return block;
}

void m_alloc(size_t size) 
{
	struct block_meta *block;

	if (size <= 0) {
		return NULL;
	}

	if (!global_base) { // first run
		block = request_space(NULL, size);
		if (!block) {
			return NULL;
		}
		global_base = block;
	} else {
		struct block_meta *last = global_base;
		block = find_free_block(&last, size);
		if (!block) { // no free blocks
			block = request_space(last, size);
			if (!block) {
				return NULL;
			}
		} else {
			block->free = 0;
		}
	}

	return block + 1;
}

struct block_meta *get_block_ptr(void *ptr) 
{
	return (struct block_meta *)ptr - 1;
}

void m_free(void *ptr) 
{
	if (!ptr) {
		return;
	}

	struct block_meta *block_ptr = get_block_ptr(ptr);
	assert(block_ptr->free == 0);
	block_ptr->free = 1;
}

void *m_realloc(void *ptr, size_t size)
{
	if (!ptr) {
		return m_alloc(size);
	}

	struct block_meta *block_ptr = get_block_ptr(ptr);
	if (block_ptr->size >= size) {
		// we have enough space
		return ptr;
	}
	
	// here the real reallocation comes
	void *new_ptr;
	new_ptr = m_alloc(size);
	if (!new_ptr) {
		return NULL;
	}
	
	memcpy(new_ptr, ptr, block_ptr->size);
	m_free(ptr);
	return new_ptr;
}

void *m_calloc(size_t nelem, size_t elsize) 
{
	size_t size = nelem * elsize;
	void *ptr = m_alloc(size);
	memset(ptr, 0, size);
	return ptr;
}

