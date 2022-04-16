#include <math.h>
#include <stdio.h>

#include "scheduling_sim.h"
#include "scheduling_utility.h"

// ---------------------------------------------------------------------------
// Example schedulers
// ---------------------------------------------------------------------------

void fcfs(scheduler_context_t *ctx)
{
	process_t *selected = get_process(ctx, 0);
	schedule_process(ctx, selected);
}

void round_robin(scheduler_context_t *ctx)
{
	process_t *selected = get_process(ctx, 0);
	schedule_process(ctx, selected);
	move_process_to_end(ctx, selected);
}

// ---------------------------------------------------------------------------
// Implement your schedulers here
// ---------------------------------------------------------------------------
void srtf(scheduler_context_t *ctx)
{
	process_t *selected = get_process(ctx, 0);

	for (size_t i = 0; i < get_num_processes(ctx); i++)
	{

		if (get_process(ctx, i)->remaining_time < selected->remaining_time)
		{
			selected = get_process(ctx, i);
		}
	}
	schedule_process(ctx, selected);
}

void round_robin_q4(scheduler_context_t *ctx)
{
	process_t *selected = get_process(ctx, 0);
	selected->user1++;
	schedule_process(ctx, selected);
	if (selected->user1 == 4)
	{
		selected->user1 = 0;
		move_process_to_end(ctx, selected);
	}
}
//---------------------------------------------------------------------------
void hpf_p(scheduler_context_t *ctx)
{
	process_t *selected = get_process(ctx, 0);

	for (size_t i = 0; i < get_num_processes(ctx); i++)
	{
		if (get_process(ctx, i)->priority > selected->priority)
		{
			selected = get_process(ctx, i);
		}
	}
	schedule_process(ctx, selected);
}

void hpf_np(scheduler_context_t *ctx)
{
	process_t *selected = get_process(ctx, 0);

	if (selected->user1 == 0)
	{
		for (size_t i = 0; i < get_num_processes(ctx); i++)
		{

			if (get_process(ctx, i)->priority > selected->priority)
			{
				selected = get_process(ctx, i);
			}
			else if (get_process(ctx, i)->priority == selected->priority)
			{

				if (get_process(ctx, i)->arrival_time < selected->arrival_time)
				{

					selected = get_process(ctx, i);
				}
			}
		}
	}
	schedule_process(ctx, selected);
	selected->user1 = 1;
}

void my_scheduler(scheduler_context_t* ctx){
    size_t number_processes = get_num_processes(ctx); //keeps changing every step
    process_t* selected;

    process_t* process_max_priority  = get_process(ctx,0); //new reference on this array in the memory
    process_max_priority->user3 = process_max_priority->priority;
    for (size_t i = 0; i < number_processes; i++)
    {
        process_t* process_next = get_process(ctx,i);
        process_next->user3 = process_next->priority + process_next->user2;
        process_next->user2++; //all process that are here are increment by 1
            if (process_max_priority->user3 < process_next->user3) //if they have the same priority keep that one that was first in, so do not change process_max_priority
        {
            process_max_priority = process_next; //update process_max_priority 
        }
    } //only exit the for loop if all actual processes compared

    selected = process_max_priority; //update it
    selected->user2++;
    schedule_process(ctx,selected);
    return;

}
// ---------------------------------------------------------------------------

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Error: Usage: %s <filename>\nExample: %s input.csv\n", argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	simulation_data_t *data = read_simulation_data(argv[1]);
	if (data == NULL)
	{
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
	// print_schedule(stdout, compute_schedule(data, my_scheduler), data);

	// -----------------------------------------------------------------------

	free_simulation_data(data);

	return EXIT_SUCCESS;
}