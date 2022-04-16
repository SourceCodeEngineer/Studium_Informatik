#include <math.h>
#include <stdio.h>

#include "scheduling_sim.h"
#include "scheduling_utility.h"

// ---------------------------------------------------------------------------
// Example schedulers
// ---------------------------------------------------------------------------

void fcfs(scheduler_context_t* ctx) {
	process_t* selected = get_process(ctx, 0);
	schedule_process(ctx, selected);
}

void round_robin(scheduler_context_t* ctx) {
	process_t* selected = get_process(ctx, 0);
	schedule_process(ctx, selected);
	move_process_to_end(ctx, selected);
}

// ---------------------------------------------------------------------------
// Implement your schedulers here
// ---------------------------------------------------------------------------

void srtf(scheduler_context_t* ctx) {

	process_t* selected = get_process(ctx, 0);
	
	for(size_t i = 0; i < get_num_processes(ctx); i++) { //go through all ready processes and select the shortest time rem
	
		if(get_process(ctx, i) -> remaining_time < selected ->remaining_time) {
			selected = get_process(ctx,i);
		}
		
	}

	schedule_process(ctx, selected);
}

void round_robin_q4(scheduler_context_t* ctx) {

	process_t* selected = get_process(ctx, 0);
	
	if(selected -> user1 < 3) { //use "user1" to check how often the process was already scheduled
		selected -> user1 += 1;
	}
	else{
		selected -> user1 = 0;
		move_process_to_end(ctx, selected);
	}
	schedule_process(ctx, selected);

}

// ---------------------------------------------------------------------------

void hpf_p(scheduler_context_t* ctx) {
	
	process_t* selected = get_process(ctx,0);
	
	for(size_t i = 0; i < get_num_processes(ctx); i++) {
	
		if(get_process(ctx, i) -> priority > selected -> priority) { //select the hpp out of all ready processes and schedule it
			selected = get_process(ctx,i);
		}
		else if(get_process(ctx, i) -> priority == selected -> priority) { //if two have same priority first come first serve
		
			if(get_process(ctx, i) -> arrival_time < selected -> arrival_time) {
				selected = get_process(ctx,i);
			}
		}
		
	}
	schedule_process(ctx, selected);	
}

void hpf_np(scheduler_context_t* ctx) {
	
	process_t* selected = get_process(ctx,0);
	
	if(get_num_processes(ctx) > 1 && get_process(ctx, 1) -> priority <= selected -> priority) { //fcfs + always block lower priority
			move_process_to_end(ctx, get_process(ctx, 1));
	}
	
	else if(get_num_processes(ctx) > 1 && get_process(ctx, 1) -> priority > selected -> priority 
			&& selected -> service_time == selected -> remaining_time) { //block when process has been already scheduled, else select highest priority 
			selected = get_process(ctx,1);
	}
	
	schedule_process(ctx, selected);	
}

// ---------------------------------------------------------------------------

void my_scheduler(scheduler_context_t* ctx) {

	process_t* selected = get_process(ctx,0);	
	
	for(size_t i = 0; i < get_num_processes(ctx); i++) {
		if(get_process(ctx, i) -> priority > selected -> priority) { //select the hpp out of all ready processes and schedule it
			selected = get_process(ctx,i);
		}
		else if(get_process(ctx, i) -> priority == selected -> priority) { //if two have same priority first come first serve
		
			if(get_process(ctx, i) -> arrival_time < selected -> arrival_time) {
				selected = get_process(ctx,i);
			}
		}
	}
	
	for(size_t i = 0; i < get_num_processes(ctx); i++) { 
	
		if((get_timestep(ctx) - (get_process(ctx, i) -> arrival_time)) > 7) { //if the process has been waiting for more than 10 timesteps it will be processed so it wont starve
			selected = get_process(ctx,i);
		}
	}
	
	schedule_process(ctx, selected);	
}
// ---------------------------------------------------------------------------

int main(int argc, char** argv) {
	if(argc != 2) {
		fprintf(stderr, "Error: Usage: %s <filename>\nExample: %s input.csv\n", argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	simulation_data_t* data = read_simulation_data(argv[1]);
	if(data == NULL) {
		fprintf(stderr, "Error: Unable to open the file '%s' for reading!\n", argv[1]);
		return EXIT_FAILURE;
	}
	print_simulation_data(stdout, data);

	// -----------------------------------------------------------------------
	// Uncomment these calls to your schedulers
	// -----------------------------------------------------------------------

	// Examples
	print_schedule(stdout, compute_schedule(data, fcfs), data);
	print_schedule(stdout, compute_schedule(data, round_robin), data);

	// Task 1
	print_schedule(stdout, compute_schedule(data, srtf), data);
	print_schedule(stdout, compute_schedule(data, round_robin_q4), data);

	// Task 2
	print_schedule(stdout, compute_schedule(data, hpf_p), data);
	print_schedule(stdout, compute_schedule(data, hpf_np), data);

	// Task 3
	print_schedule(stdout, compute_schedule(data, my_scheduler), data);

	// -----------------------------------------------------------------------

	free_simulation_data(data);

	return EXIT_SUCCESS;
}
