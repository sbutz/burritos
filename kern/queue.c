#include <stddef.h>

#include "queue.h"
#include "pmm.h"

struct node {
	void *v;
	struct node *next;
};

struct queue {
	struct node *head;
	struct node *tail;
};

struct queue *
queue_init()
{
	struct queue *q;

	q = pmm_alloc();
	q->head = NULL;
	q->tail = NULL;

	return q;
}

void
queue_push(struct queue *q, void *v)
{
	struct node *n;

	//TODO: assert(q != NULL);

	n = pmm_alloc();
	n->v = v;
	n->next = NULL;
	if (q->tail != NULL)
		q->tail->next = n;
	else
		q->head = n;
	q->tail = n;
}

void *
queue_pop(struct queue *q)
{
	struct node *n;
	void *v;

	//TODO: assert(q != NULL);

	if (q->head == NULL)
		return NULL;

	n = q->head;
	v = n->v;
	q->head = n->next;
	if (q->head == NULL)
		q->tail = NULL;
	pmm_free(n);
	return v;
}

void
queue_free(struct queue *q)
{
	//TODO: assert(q != NULL);

	while (q->head != NULL)
		queue_pop(q);

	pmm_free(q);
}
