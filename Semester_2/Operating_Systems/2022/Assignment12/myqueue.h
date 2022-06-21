#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>


struct order
{
	int guestID;
	int foodID;
};
struct myqueue_entry
{
	struct order order;
	STAILQ_ENTRY(myqueue_entry) entries;
};

STAILQ_HEAD(myqueue_head, myqueue_entry);

typedef struct myqueue_head myqueue;

static void myqueue_init(myqueue * q)
{
	STAILQ_INIT(q);
}

static bool myqueue_is_empty(myqueue * q)
{
	return STAILQ_EMPTY(q);
}

static void myqueue_push(myqueue * q, struct order order)
{
	struct myqueue_entry * entry = (struct myqueue_entry *)malloc(sizeof(struct myqueue_entry));
	entry->order = order;
	STAILQ_INSERT_TAIL(q, entry, entries);
}

static struct order myqueue_pop(myqueue * q)
{
	assert(!myqueue_is_empty(q));
	struct myqueue_entry * entry = STAILQ_FIRST(q);
	const struct order order = entry->order;
	STAILQ_REMOVE_HEAD(q, entries);
	free(entry);
	return order;
}

#endif