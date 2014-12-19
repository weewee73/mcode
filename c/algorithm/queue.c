#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void empty_queue(queue_t *q)
{
    unsigned int i;

    if (NULL == q) {
        return ;
    }
    q->head = q->tail = q->count = 0;

    if (NULL == q->buf) {
        return ;
    }

    for (i=0; i<q->length; i++) {
        q->buf[i] = -1;
    }
}

queue_t *init_queue(unsigned int length)
{
    queue_t *q;

    q = (queue_t *)malloc(sizeof(queue_t));
    if (NULL == q) {
        printf("malloc queue_t error!\n");
        return NULL;
    }

    q->length = length;

    q->buf = (int *)malloc(q->length);
    if (NULL == q->buf) {
        printf("malloc queue buffer error!\n");
        free(q);
        return NULL;
    }

    empty_queue(q);

    return q;
}

void destroy_queue(queue_t *q)
{
    if (NULL == q) {
        return ;
    }

    if (NULL != q->buf) {
        free(q->buf);
    }

    free(q);
}

int dequeue(queue_t *q, int *x)
{
    if (NULL == q || NULL == q->buf) {
        return E_QUEUE_ERROR;
    }

    if (q->count == 0) {
        return E_QUEUE_EMPTY;
    }

    *x = q->buf[q->head];
    q->buf[q->head] = -1;
    if (q->head == q->length-1) {
        q->head = 0;
    }
    else {
        q->head++;
    }

    q->count--;

    return E_QUEUE_SUC;
}

int  enqueue(queue_t *q, int x)
{
    if (NULL == q || NULL == q->buf) {
        return E_QUEUE_ERROR;
    }

    if (q->count == q->length) {
        return E_QUEUE_FULL;
    }

    q->buf[q->tail] = x;

    if (q->tail == q->length-1) {
        q->tail = 0;
    }
    else {
        q->tail++;
    }

    q->count++;

    return E_QUEUE_SUC;
}

void dump_quene(queue_t *q)
{
    unsigned int i;
    if (NULL == q)
        return;

    printf("\n================================\n");
    printf("\tq->length=%d\n", q->length);
    printf("\tq->head=%d\n", q->head);
    printf("\tq->tail=%d\n", q->tail);
    printf("\tq->count=%d\n", q->count);
    printf("--------------------------------\n");

    if (NULL == q->buf)
        return;

    for (i=0; i<q->length; i++) {
        printf("%d: %d\t", i, q->buf[i]);
    }

    printf("\n\n");

}

void queue_test()
{
    queue_t *q = NULL;
    int i;
    int x, ret;

    q = init_queue(5);

    for (i=0; i<5; i++) {
        enqueue(q, i);
    }

    dump_quene(q);

    printf("enqueue 111:\n");
    enqueue(q, 111);
    printf("enqueue 222:\n");
    enqueue(q, 222);

    dump_quene(q);


    ret = dequeue(q, &x);
    printf("dequeue[%d] %d!\n", ret, x);
    ret = dequeue(q, &x);
    printf("dequeue[%d] %d!\n", ret, x);
    ret = dequeue(q, &x);
    printf("dequeue[%d] %d!\n", ret, x);
    printf("\n\n");


    printf("enqueue 333:\n");
    enqueue(q, 333);
    printf("\n\n");

    dump_quene(q);

    empty_queue(q);
    dump_quene(q);
}

int main()
{
    queue_test();
    return 0;
}
