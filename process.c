#include "process.h"
//TAKEN FROM CP264 AND MODIFIED

PROCESS* new_process(int start, int id, int run, int exchange[]) {
	PROCESS *pcs = (PROCESS*) malloc(sizeof(PROCESS));
	pcs->start = start;
	pcs->pid = id;
	pcs->run = run;
	pcs->exchange_int = 0;
	pcs->ready = 0;
	pcs->blocked = 0;
	pcs->current_runtime = 0;
	pcs->suspended_time = 0;
	pcs->num_exchanges = 0;
	pcs->ready_timer = 0;
	pcs->total_suspended = 0;
	pcs->remaining_runtime = run;
	
	//Temperary cause flexible array no work
	int i = 0;
	while (exchange[i] != 0) {
		pcs->exchange[i] = exchange[i];
		i++;
	}
	
	
	
	return pcs;
}