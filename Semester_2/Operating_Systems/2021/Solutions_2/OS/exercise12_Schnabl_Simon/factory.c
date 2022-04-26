#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>
#include <string.h>

#define MAXWORKERS 20

_Atomic int doors = 0;
_Atomic int knobs = 0;
_Atomic int knobs_total = 0;
_Atomic int pot_doors = 0;
_Atomic int max = 0;

pthread_mutex_t mutex;

void *worker(void *arg)
{
	unsigned int seed = (unsigned)pthread_self();
	double lazyn = (double)rand_r(&seed) / RAND_MAX;
	if ((*(int *)arg) == 1)
	{
		while (doors < max)
		{
			if (doors > max)
			{
				break;
			}
			usleep((10 + lazyn * 30) * 1000);
			knobs++;
			knobs_total++;
		}
	}

	while (doors < max)
	{
		if (knobs > 0)
		{
			if (doors > max)
			{
				break;
			}
			knobs--;
			usleep((10 + lazyn * 90) * 1000);
			doors++;
		}
		usleep((10 + lazyn * 90) * 1000);
		pot_doors++;
	}

	pthread_exit(0);
}

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		perror("Usage: <enable load balancing> <number of doors to produce>");
		return EXIT_FAILURE;
	}

	pthread_mutex_init(&mutex, NULL);

	pthread_t knob[MAXWORKERS];
	pthread_t door[MAXWORKERS];

	max = atoi(argv[2]);

	for (int i = 0; i < MAXWORKERS / 2; i++)
	{
		int *arg = malloc(sizeof(*arg));
		*arg = 1;
		pthread_create(&knob[i], NULL, worker, arg);
	}

	for (int i = 0; i < MAXWORKERS / 2; i++)
	{
		int *arg = malloc(sizeof(*arg));
		*arg = 0;
		pthread_create(&door[i], NULL, worker, arg);
	}

	int i1 = 0, i2 = 0;
	double tmp1 = 0.0, tmp2 = 0.0, time = 1.0;

	if (atoi(argv[1]) == 1)
	{

		int pos1 = 10;
		int pos2 = 10;

		while (doors < max)
		{
			sleep(1);
			pthread_mutex_lock(&mutex);
			tmp1 = knobs_total / time;
			tmp2 = (doors + pot_doors) / time;
			printf("Producing %.2f knobs/s, %.2f doors/s\n", tmp1, tmp2);
			pthread_mutex_unlock(&mutex);
			if (doors > max)
			{
				break;
			}
			else if ((tmp1 * 1.1) < tmp2)
			{
				pthread_cancel(door[i1]);
				int *arg = malloc(sizeof(*arg));
				*arg = 1;
				pthread_create(&knob[pos1], NULL, worker, arg);
				pos1++;
				i1++;
				time++;
				printf("Worker reassigned: %d knobs, %d doors\n\n", 20 - (pos2 + MAXWORKERS / 2 - pos1), pos2 + MAXWORKERS / 2 - pos1);
			}
			else if ((tmp2 * 1.1) < tmp1)
			{
				pthread_cancel(knob[i2]);
				int *arg = malloc(sizeof(*arg));
				*arg = 0;
				pthread_create(&door[pos2], NULL, worker, arg);
				pos2++;
				i2++;
				time++;
				printf("Worker reassigned: %d knobs, %d doors\n\n", MAXWORKERS / 2 - i2, pos2 + MAXWORKERS / 2 - 10);
			}
		}
	}
	else
	{
		while (doors < max)
		{
			sleep(1);
			pthread_mutex_lock(&mutex);
			tmp1 = knobs_total / time;
			tmp2 = (doors + pot_doors) / time;
			printf("Producing %.2f knobs/s, %.2f doors/s\n", tmp1, tmp2);
			pthread_mutex_unlock(&mutex);
			time++;
		}
	}

	for (int i = 0; i < MAXWORKERS / 2; i++)
	{
		pthread_join(knob[i + i1], NULL);
		pthread_join(door[i + i2], NULL);
	}

	pthread_mutex_unlock(&mutex);
	printf("Total knobs: %d\n", knobs_total);
	printf("Total doors produced in %.0fs: %d\n", time, doors);

	return EXIT_SUCCESS;
}
