#include "queue.h"
//TAKEN FROM CP264 AND MODIFIED

void enqueue(QNODE **frontp, QNODE **rearp, PROCESS *p) 
{
// your code
	QNODE *node = (QNODE*) malloc(sizeof(QNODE));
	QNODE *ptr = *rearp;
	node->p = p;
	
	if (*frontp == NULL) {
		*frontp = node;
		node->next = NULL;
		*rearp = node;
	}
	else {
		ptr->next = node;
		*rearp = node;
		node->next = NULL;
	}
}

PROCESS* dequeue(QNODE **frontp, QNODE **rearp) 
{
// your code
	PROCESS *p;
	
	if (*frontp == NULL) {
		printf("NOTHING TO REMOVE\n");
	}
	else {
		p = (*frontp)->p;
		QNODE *ptr = *frontp;
		*frontp = (*frontp)->next;
		free(ptr);
	}
	
	return p;
}

int peek(QNODE *front) 
{
// your code
	QNODE *ptr = front;
	
	int value = ptr->p->start;
	
	return value;
}

int is_empty(QNODE *front) {
	if (front) {
		return 1;
	}
	else {
		return 0;
	}
}