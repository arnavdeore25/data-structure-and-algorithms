#include "orderqueue.h"
#include <stdlib.h>

void initQueue(OrderQueue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

int enqueue(OrderQueue *queue, Order order)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        return 0;  
    }

    newNode->order = order;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;

    return 1;
}

int dequeue(OrderQueue *queue, Order *order)
{
    if (queue->front == NULL) {
        return 0;
    }

    Node *temp = queue->front;
    *order = temp->order;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);

    queue->size--;

    return 1;
}

int peek(const OrderQueue *queue, Order *order)
{
    if (queue->front == NULL) {
        return 0;  
    }

    *order = queue->front->order;

    return 1;
}

int isEmpty(const OrderQueue *queue)
{
    return queue->front == NULL;
}

void destroyQueue(OrderQueue *queue)
{
    Node *current = queue->front;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}