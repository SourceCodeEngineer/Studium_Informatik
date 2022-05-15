#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <pthread.h>
#include <semaphore.h>

typedef void *(*job_function)(void *);
typedef void *job_arg;

typedef struct job
{
	job_function routine;
	job_arg arg;
	sem_t* workerLock;
} job;

struct myqueue_entry
{
	job jobs;
	STAILQ_ENTRY(myqueue_entry)
	entries;
};

STAILQ_HEAD(myqueue_head, myqueue_entry);

typedef struct myqueue_head myqueue;

static void myqueue_init(myqueue *q)
{
	STAILQ_INIT(q);
}

static bool myqueue_is_empty(myqueue *q)
{
	return STAILQ_EMPTY(q);
}

static void myqueue_push(myqueue *q, job job)
{
	struct myqueue_entry *entry = malloc(sizeof(struct myqueue_entry));
	entry->jobs = job;
	STAILQ_INSERT_TAIL(q, entry, entries);
}

static job myqueue_pop(myqueue *q)
{
	assert(!myqueue_is_empty(q));
	struct myqueue_entry *entry = STAILQ_FIRST(q);
	const job job = entry->jobs;
	STAILQ_REMOVE_HEAD(q, entries);
	free(entry);
	return job;
}

#endif