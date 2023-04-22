#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

PriorityQueue* createPriorityQueue() {
    PriorityQueue* q = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    q->front = NULL;
    return q;
}

void enqueuePriority(PriorityQueue* q, int data, int priority) {
    PriorityQueueNode* newNode = (PriorityQueueNode*) malloc(sizeof(PriorityQueueNode));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    if (q->front == NULL || q->front->priority > priority) {
        newNode->next = q->front;
        q->front = newNode;
    } else {
        PriorityQueueNode* temp = q->front;
        while (temp->next != NULL && temp->next->priority < priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

int dequeuePriority(PriorityQueue* q) {
    if (q->front == NULL) {
        return -1;
    }
    PriorityQueueNode* temp = q->front;
    int data = temp->data;
    q->front = temp->next;
    free(temp);
    return data;
}

int peekPriority(PriorityQueue* q) {
    if (q->front == NULL) {
        return -1;
    }
    return q->front->data;
}

int isPriorityQueueEmpty(PriorityQueue* q) {
    return q->front == NULL;
}

void freePriorityQueue(PriorityQueue* q) {
    PriorityQueueNode* temp;
    while (q->front != NULL) {
        temp = q->front;
        q->front = temp->next;
        free(temp);
    }
    free(q);
}
