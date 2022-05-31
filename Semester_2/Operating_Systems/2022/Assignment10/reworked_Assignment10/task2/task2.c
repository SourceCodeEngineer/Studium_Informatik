#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <pthread.h>
#include <errno.h>
#include <stdatomic.h>
#include <semaphore.h>
#include <string.h>
#include <sys/mman.h>


#ifdef GLOBAL_BENCH_BUILTIN_ALLOC
#include "../tests/membench.h"
#endif
#ifdef GLOBAL_BENCH
#include "../tests/membench.h"
#endif
#ifdef TESTS
#include "../tests/allocator_tests.h"
#endif


typedef struct mem_block_str mem_block_t; 


struct mem_block_str{
    mem_block_t *next;
    mem_block_t *prev;
    size_t size;
    uint8_t data[];
};
#ifndef THREAD_LOCAL
pthread_mutex_t mutex;
mem_block_t *start_of_mem = NULL;
mem_block_t *next_free_block = NULL;
void *end_of_mem = NULL;
size_t mem_size=0;
#else
_Thread_local mem_block_t *start_of_mem = NULL;
_Thread_local mem_block_t *next_free_block = NULL;
_Thread_local void *end_of_mem = NULL;
_Thread_local size_t mem_size=0;
#endif

void my_allocator_init(size_t size)
{
    #ifndef THREAD_LOCAL
    pthread_mutex_init(&mutex,NULL);
    #endif
    start_of_mem = mmap(NULL,size,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    mem_size = size;
    end_of_mem = (void *) ((uint8_t *) start_of_mem + size);
    next_free_block = start_of_mem;
    next_free_block->next=NULL;
    next_free_block->prev=NULL;
    next_free_block->size=mem_size-sizeof(mem_block_t);
}

void my_allocator_destroy(void)
{
    munmap(start_of_mem,mem_size);
    start_of_mem = NULL;
    next_free_block = NULL;
    end_of_mem = NULL;
    #ifndef THREAD_LOCAL
    pthread_mutex_destroy(&mutex);
    #endif
    mem_size = 0;
}

void* my_malloc(size_t size)
{
    #ifndef THREAD_LOCAL
    pthread_mutex_lock(&mutex);
    #endif
    mem_block_t *best_fit = NULL;
    mem_block_t *current = next_free_block;
    while (current!=NULL){
        if (current->size >= size)
        {
            if (best_fit==NULL || current->size - size < best_fit->size - size){
                best_fit=current;
            }
        }
        current = current->next;
    }
    //check for out of memory (or no block big enough found)
    if (best_fit == NULL){
        errno=ENOMEM;
        #ifndef THREAD_LOCAL
        pthread_mutex_unlock(&mutex);
        #endif
        return NULL;
    }
    //calculate how big the remaining memory block would be (without the required header)
    if (best_fit->size <= size + sizeof(mem_block_t)) // use whole block
    {
        if (best_fit->prev == NULL) //has no predecessor
        {
            next_free_block=best_fit->next;
            if (next_free_block!=NULL){
                next_free_block->prev=NULL;
            }
        }else{
            best_fit->prev->next = best_fit->next;
            if (best_fit->next != NULL){
                best_fit->next->prev = best_fit->prev;
            }
       }
    }else{ // create a new free block within best_fit and link that to the others
        size_t remaining_size = best_fit->size - (size + sizeof(mem_block_t));
        mem_block_t *remaining_block = (mem_block_t *)((uint8_t *)best_fit->data + size);
        remaining_block->size = remaining_size;
        remaining_block->prev = best_fit->prev;
        remaining_block->next = best_fit->next;
        if (remaining_block->prev == NULL){
            next_free_block = remaining_block;
        }else{
            remaining_block->prev->next=remaining_block;
        }
        if (remaining_block->next != NULL){
            remaining_block->next->prev=remaining_block;
        }
        best_fit->size=size;
    }
    #ifndef THREAD_LOCAL
    pthread_mutex_unlock(&mutex);
    #endif
    return (void *) best_fit->data;
}

void my_free(void* ptr)
{
    #ifndef THREAD_LOCAL
    pthread_mutex_lock(&mutex);
    #endif
    mem_block_t *block_to_free = (mem_block_t *) ((uint8_t *)ptr - sizeof(mem_block_t));
    if (next_free_block==NULL) // this is the only free block available
    {
        block_to_free->prev=NULL;
        block_to_free->next=NULL;
        next_free_block=block_to_free;
        #ifndef THREAD_LOCAL
        pthread_mutex_unlock(&mutex);
        #endif
        return;
    }
    if (next_free_block>block_to_free){ // this block is before all other blocks
        block_to_free->prev=NULL;
        block_to_free->next=next_free_block;
        if (block_to_free->next != NULL){
            block_to_free->next->prev=block_to_free;
        }
        next_free_block=block_to_free;
    }else{
        block_to_free->prev=next_free_block;
        block_to_free->next=next_free_block->next;
        //traverse list of free blocks until the block thas is about to be free'd is between 2 free blocks
        while (block_to_free->next != NULL && block_to_free->next<block_to_free){
            block_to_free->prev=block_to_free->next;
            block_to_free->next=block_to_free->prev->next;
        }
    }
    //check if blocks can be merged
    //start with previous block
    if (block_to_free->prev != NULL && 
            (uint8_t *) block_to_free->prev+block_to_free->prev->size+sizeof(mem_block_t)==(uint8_t *)block_to_free){
        size_t additional_size = block_to_free->size+sizeof(mem_block_t);
        block_to_free=block_to_free->prev;
        block_to_free->size+=additional_size;
    }
    //check if next block can be merged
    if (block_to_free->next != NULL && (uint8_t *) block_to_free->next == (uint8_t *) block_to_free + block_to_free->size + sizeof(mem_block_t)){
        block_to_free->size += block_to_free->next->size + sizeof(mem_block_t);
        block_to_free->next = block_to_free->next->next;
    }
    //reroute all pointers
    if (block_to_free->prev != NULL)
    {
        block_to_free->prev->next=block_to_free;
    }
    if (block_to_free->next != NULL)
    {
        block_to_free->next->prev=block_to_free;
    }
    #ifndef THREAD_LOCAL
    pthread_mutex_unlock(&mutex);
    #endif
}


int main(void){
    #ifdef TESTS
    test_best_fit_allocator();
    #endif
    #ifdef GLOBAL_BENCH
        #ifndef THREAD_LOCAL
        run_membench_global(my_allocator_init,my_allocator_destroy,my_malloc,my_free);
        #else
        run_membench_thread_local(my_allocator_init,my_allocator_destroy,my_malloc,my_free);
        #endif
    #endif
    #ifdef GLOBAL_BENCH_BUILTIN_ALLOC
    run_membench_global(my_allocator_init,my_allocator_destroy,malloc,free);
    #endif
    return EXIT_SUCCESS;
}