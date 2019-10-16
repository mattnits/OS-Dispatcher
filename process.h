#ifndef PROCESS_H
#define PROCESS_H
//TAKEN FROM CP264 AND MODIFIED

#include <stdio.h>
#include <malloc.h>

typedef struct process {
	int start;
	int pid;
	int run;
	int exchange[100];
	int exchange_int;
	int num_exchanges;
	int ready;
	int blocked;
	int current_runtime;
	int remaining_runtime;
	int suspended_time;
	int ready_timer;
	int total_suspended;
	
} PROCESS;

PROCESS* new_process(int start, int id, int run, int exchange[]);

#endif