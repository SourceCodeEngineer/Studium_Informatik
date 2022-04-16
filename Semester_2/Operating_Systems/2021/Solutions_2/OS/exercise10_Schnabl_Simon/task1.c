#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "membench.c"

#define BLOCK_SIZE 1024

typedef struct block_t {
	struct block_t *next;
	void* mem;
} block_t;

typedef struct {
	void* head;
	void* tail;
	size_t size;
	block_t* next_free;
} mem_pool_t;

mem_pool_t global_pool; 
void *global_ptr;
pthread_mutex_t pool_mutex;

void my_allocator_init(size_t size) {
	
	global_pool.head = malloc(size);
	global_pool.tail = global_pool.head + size;
	global_pool.size = size;
	global_pool.next_free = (block_t *)global_pool.head;
	
	pthread_mutex_init(&pool_mutex, NULL);
	
	global_ptr = global_pool.head;
	size_t step = sizeof(block_t) + BLOCK_SIZE;
	
	while((global_pool.head + size) - global_ptr >= (long int) step) {
		block_t* block = (void *) global_ptr;
		block -> mem = global_ptr + sizeof(block_t);
		block -> next = (block_t*)(global_ptr + step);
		global_ptr += step;
	}
	((block_t *) global_ptr) -> next = NULL;
}

void my_allocator_destroy() {
	free(global_pool.head);
	pthread_mutex_destroy(&pool_mutex);
}

void my_free(void *ptr) {
	pthread_mutex_lock(&pool_mutex);
	block_t* block = global_pool.head;
	block -> next = global_pool.next_free;
	global_pool.next_free = block;
	pthread_mutex_unlock(&pool_mutex);
}

void* my_malloc(size_t size) {
	pthread_mutex_lock(&pool_mutex);
	if(size > BLOCK_SIZE) {
		return NULL;
	}
	else if(global_pool.next_free == NULL) {
		return NULL;
	}
	else if(global_pool.next_free != NULL) {
		void* ret = global_pool.next_free -> mem;
		global_pool.next_free = global_pool.next_free -> next;
		pthread_mutex_unlock(&pool_mutex);
		return ret;
	}
	pthread_mutex_unlock(&pool_mutex);
	return NULL;
}

int main() {
	run_membench_global(my_allocator_init, my_allocator_destroy, my_malloc, my_free);
}
