#include <stdio.h>
#include "alloc.h"

void *global_base = NULL;

/*
 * searches for already allocated memory block to use it
 * by iterating over the linked list of already created blocks
 */
struct block_meta *find_free_block(struct block_meta **last, size_t size) 
{
	struct block_meta *curr = global_base;
	while (curr && curr->size < size) {
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
	void *request = sbrk(size + META_SIZE); // increments process's data segment by size + META_SIZE bytes
	assert((void *)block == request);
	if (request == (void *) -1) {
		return NULL;
	}

	if (last) {
		last->next = block;
	}
	
	block->size = size;
	block->next = NULL;
	return block;
}

/*
 * malloc clone
 */
void *m_alloc(size_t size) 
{
	struct block_meta *block;

	if (size < 0) {
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
		}
	}

	return block + 1;
}

void m_free(void *ptr) 
{

}

void print_blocks() 
{
	struct block_meta *curr = global_base;
	while (curr) {
		printf("%p, %zu\n", curr, curr->size);
		curr = curr->next;
	}

	printf("done\n");
}

