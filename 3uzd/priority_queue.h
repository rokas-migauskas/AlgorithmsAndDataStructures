#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct PriorityQueueNode {
    int data;
    int priority;
    struct PriorityQueueNode* next;
} PriorityQueueNode;

typedef struct PriorityQueue {
    PriorityQueueNode* front;
} PriorityQueue;

PriorityQueue* createPriorityQueue();
void enqueuePriority(PriorityQueue* q, int data, int priority);
int dequeuePriority(PriorityQueue* q);
int peekPriority(PriorityQueue* q);
int isPriorityQueueEmpty(PriorityQueue* q);
void freePriorityQueue(PriorityQueue* q);

#endif
