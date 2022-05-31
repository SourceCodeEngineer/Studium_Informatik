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

#define BLOCK_SIZE 1024

typedef struct mem_block_str mem_block_t; 


struct mem_block_str{
    mem_block_t *next;
    uint8_t data[BLOCK_SIZE];
};

#ifndef THREAD_LOCAL
pthread_mutex_t mutex;
mem_block_t *start_of_mem = NULL;
mem_block_t *next_free_block = NULL;
size_t mem_size=0;
#else
_Thread_local mem_block_t *start_of_mem = NULL;
_Thread_local mem_block_t *next_free_block = NULL;
_Thread_local size_t mem_size=0;
#endif

void my_allocator_init(size_t size)
{
    #ifndef THREAD_LOCAL
    pthread_mutex_init(&mutex,NULL);
    #endif
    start_of_mem = mmap(NULL,size,PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
    mem_size = size;
    next_free_block = start_of_mem;
    size_t numOfBlocks=size/sizeof(mem_block_t);
    for (size_t i=0;i<numOfBlocks;i++){
        start_of_mem[i].next=(start_of_mem+i+1);
    }
    //last element->next = NULL
    start_of_mem[numOfBlocks-1].next=NULL;

}

void my_allocator_destroy(void)
{
    munmap(start_of_mem,mem_size);
    start_of_mem = NULL;
    next_free_block = NULL;
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
    if (size > BLOCK_SIZE || next_free_block == NULL)
    {
        errno=ENOMEM;
        #ifndef THREAD_LOCAL
        pthread_mutex_unlock(&mutex);
        #endif
        return NULL;
    }
    mem_block_t *current = next_free_block;
    next_free_block=current->next;
    #ifndef THREAD_LOCAL
    pthread_mutex_unlock(&mutex);
    #endif
    return (void *) current->data;
}

void my_free(void* ptr)
{
    #ifndef THREAD_LOCAL
    pthread_mutex_lock(&mutex);
    #endif
    mem_block_t *block_to_free = (mem_block_t *) ((uint8_t *)ptr - sizeof(next_free_block->next));
    block_to_free->next=next_free_block;
    next_free_block=block_to_free;
    #ifndef THREAD_LOCAL
    pthread_mutex_unlock(&mutex);
    #endif
}


int main(void){
    #ifdef TESTS
    test_free_list_allocator();
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