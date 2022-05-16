#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/queue.h>

typedef void (*job_function)(void *);
typedef void *job_arg;

typedef struct {
  pthread_mutex_t *job_mutex;
  pthread_cond_t *job_finished;
  bool job_has_finished;
  job_function function;
  job_arg arg;
} job;

typedef job* job_id;

struct myqueue_entry {
	job* job; 
	STAILQ_ENTRY(myqueue_entry) entries;
};

STAILQ_HEAD(myqueue_head, myqueue_entry);

typedef struct myqueue_head myqueue;

static void myqueue_init(myqueue* q) {
	STAILQ_INIT(q);
}

static bool myqueue_is_empty(myqueue* q) {
	return STAILQ_EMPTY(q);
}

static void myqueue_push(myqueue* q, job* job) {
	struct myqueue_entry* entry = malloc(sizeof(struct myqueue_entry));
	entry->job = job;
	STAILQ_INSERT_TAIL(q, entry, entries);
}

static job* myqueue_pop(myqueue* q) {
	assert(!myqueue_is_empty(q));
	struct myqueue_entry* entry = STAILQ_FIRST(q);
	job *value = entry->job;
	STAILQ_REMOVE_HEAD(q, entries);
	free(entry);
	return value;
}

#endif
