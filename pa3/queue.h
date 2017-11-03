#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>

#define QUEUE_FAILURE -1
#define QUEUE_SUCCESS 0

typedef struct queue_node_s{
  char payload[1030];
  int used;
} queue_node;

typedef struct queue_s{
  queue_node* array;
  int front;
  int rear;
  int maxSize;
} queue;

int queue_init(queue* q, int size);
int queue_is_empty(queue* q);
int queue_is_full(queue* q);
int queue_push(queue* q, char* payload);
char* queue_pop(queue* q);
void queue_cleanup(queue* q);

#endif
