#ifndef QUEUE_H
#define QUEUE_H
//TAKEN FROM CP264 AND MODIFIED

#include <stdio.h>
#include <malloc.h>
#include "process.h"

typedef struct qnode {
  struct process *p;
  struct qnode *next;
} QNODE;

void enqueue(QNODE **frontp, QNODE **rearp, PROCESS *p);
PROCESS* dequeue(QNODE **frontp, QNODE **rearp);
int peek(QNODE *front);
int is_empty(QNODE *front);

#endif