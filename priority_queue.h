#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
//TAKEN FROM CP264 AND MODIFIED

#include <stdio.h>
#include <malloc.h>
#include "process.h"

typedef struct pqnode {
  struct process *p;
  struct pqnode *next;
} PQNODE;

void enpqueue(PQNODE **frontp, PQNODE **rearp, PROCESS *p);
PROCESS* depqueue(PQNODE **frontp, PQNODE **rearp);
int pqpeek(PQNODE *front);
int pqis_empty(PQNODE *front);

#endif