#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include <stddef.h>

typedef struct {
    int order_id;
} Order;

typedef struct Node {
    Order order;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    size_t size;
} OrderQueue;

void initQueue(OrderQueue *queue);

int enqueue(OrderQueue *queue, Order order);

int dequeue(OrderQueue *queue, Order *order);

int peek(const OrderQueue *queue, Order *order);

int isEmpty(const OrderQueue *queue);

void destroyQueue(OrderQueue *queue);

#endif