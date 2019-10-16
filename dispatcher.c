/*
dispatcher.c

Dispatch Algorithm : ....
*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 100

/*
Any required standard libraries and your header files here
*/
#include "priority_queue.h"
#include "queue.h"
#include "process.h"
//INPUT: Start, ID, Run Time, Exchange Time with HD
//       100	12	800		500
//       300	11	1000		500
//       700	13	800		
//OUTPUT: ID, Run Time, Ready, Blocked

void dispatcher(FILE *fd, int harddrive){
    /*
        Your code here.
        You may edit the following code
    */
    char line_buffer[MAX_LINE_LENGTH];
    int start_time, run_time, process_id, num_exchanges, exchange_time, exchange[100], i = 0, timer = 0;
    char *token;
	QNODE *startq_front = NULL, *startq_rear = NULL;
	PQNODE *readyq_front = NULL, *readyq_rear = NULL;
	QNODE *suspendedq_front = NULL, *suspendedq_rear = NULL;
	QNODE *exitq_front = NULL, *exitq_rear = NULL;
	PROCESS *p0 = new_process(0, 0, harddrive, exchange);
	QNODE *cpu_front = NULL, *cpu_rear = NULL;
	enqueue(&cpu_front, &cpu_rear, p0);
    
    //Process simulation input line by line
    while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n') {
		i = 0;
		token = strtok(line_buffer, " ");
		sscanf(token, "%d",&start_time);

		token = strtok(NULL, " ");
		sscanf(token, "%d",&process_id);

		token = strtok(NULL, " ");
		sscanf(token, "%d",&run_time);

		num_exchanges = 0;
		token = strtok(NULL, " ");
		while ( token != NULL ){
			num_exchanges += sscanf(token, "%d",&exchange_time);
			exchange[i] = exchange_time;
			token = strtok(NULL, " ");
			i++;
		}

		enqueue(&startq_front, &startq_rear, new_process(start_time, process_id, run_time, exchange));
		startq_rear->p->num_exchanges = num_exchanges;
		printf("Process %3d wants to start at %6dms and run for %6dms and has %3d hard drive exchanges\n",  process_id, start_time, run_time, num_exchanges);    
    }
	
	//***LOOP UNTIL PROCESS IS FINISHED***
	while (startq_front != NULL || readyq_front != NULL || suspendedq_front != NULL || cpu_front->p->pid != p0->pid) {
		timer++;
		
		if (suspendedq_front != NULL) {
			if (suspendedq_front->next != NULL) {
				QNODE *temp3 = suspendedq_front->next;
				while (temp3 != NULL) {
					temp3->p->total_suspended++;
					temp3 = temp3->next;
				}
			}
			suspendedq_front->p->suspended_time++;
			
			if (suspendedq_front->p->suspended_time == harddrive) {
				suspendedq_front->p->exchange_int++;
				suspendedq_front->p->total_suspended += suspendedq_front->p->suspended_time;
				suspendedq_front->p->suspended_time = 0;
				enpqueue(&readyq_front, &readyq_rear, dequeue(&suspendedq_front, &suspendedq_rear));
			}
		}
		
		if (startq_front != NULL && timer == startq_front->p->start) {
			enpqueue(&readyq_front, &readyq_rear, dequeue(&startq_front, &startq_rear));
		}
		
		if (cpu_front->p->exchange_int < cpu_front->p->num_exchanges && cpu_front->p->current_runtime == cpu_front->p->exchange[cpu_front->p->exchange_int]) {
			enqueue(&suspendedq_front, &suspendedq_rear, dequeue(&cpu_front, &cpu_rear));
			enqueue(&cpu_front, &cpu_rear, p0);
		}
		
		if (readyq_front != NULL && cpu_front->p->pid == p0->pid) {
			dequeue(&cpu_front, &cpu_rear);
			readyq_front->p->ready += readyq_front->p->ready_timer;
			readyq_front->p->ready_timer = 0;
			enqueue(&cpu_front, &cpu_rear, depqueue(&readyq_front, &readyq_rear));
		}
		
		if (readyq_front != NULL && cpu_front->p->pid != p0->pid && (readyq_front->p->run - readyq_front->p->current_runtime) < (cpu_front->p->run - cpu_front->p->current_runtime)) {
			enpqueue(&readyq_front, &readyq_rear, dequeue(&cpu_front, &cpu_rear));
			readyq_front->p->ready += readyq_front->p->ready_timer;
			readyq_front->p->ready_timer = 0;
			enqueue(&cpu_front, &cpu_rear, depqueue(&readyq_front, &readyq_rear));
		}
		
		if (cpu_front->p->pid != p0->pid && cpu_front->p->run == cpu_front->p->current_runtime) {
			enqueue(&exitq_front, &exitq_rear, dequeue(&cpu_front, &cpu_rear));
			if (readyq_front != NULL) {
				readyq_front->p->ready += readyq_front->p->ready_timer;
				readyq_front->p->ready_timer = 0;
				enqueue(&cpu_front, &cpu_rear, depqueue(&readyq_front, &readyq_rear));
			}
			else {
				enqueue(&cpu_front, &cpu_rear, p0);
			}
		}
		
		if (readyq_front != NULL) {
			PQNODE *temp = readyq_front;
			while (temp != NULL) {
				temp->p->ready_timer++;
				temp = temp->next;
			}
		}
		if (cpu_front != NULL) {
			cpu_front->p->current_runtime++;
		}
		
	}
	

	printf("%d  %d\n", p0->pid, p0->current_runtime);
	QNODE *temp1 = exitq_front;
	while (temp1 != NULL) {
		printf("%d  %d  %d  %d\n", temp1->p->pid, temp1->p->run, temp1->p->ready, temp1->p->total_suspended);
		temp1 = temp1->next;
	}
}

