#ifndef _LIST_H
#define _LIST_H

struct queue;

struct queue * queue_init();
void queue_push(struct queue *, void *);
void *queue_pop(struct queue *);
void queue_free(struct queue *);

#endif
