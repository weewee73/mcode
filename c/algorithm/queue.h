#ifndef _QUEUE_H
#define _QUEUE_H

typedef enum _ERR_QUEUE
{
    E_QUEUE_ERROR = -1,
    E_QUEUE_SUC = 0,
    E_QUEUE_EMPTY,
    E_QUEUE_FULL,
}ERR_QUEUE;

typedef struct __queue_t {
    unsigned int length;
    unsigned int head;
    unsigned int tail;
    unsigned int count;
    int  *buf;
}queue_t;

queue_t *init_queue(unsigned int length);
void destroy_queue(queue_t *q);
void empty_queue(queue_t *q);

int enqueue(queue_t *q, int x);
int dequeue(queue_t *q, int *x);

#endif
