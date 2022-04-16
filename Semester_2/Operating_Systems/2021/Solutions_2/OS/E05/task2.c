#include <fcntl.h> 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <string.h>

#define NAME "shm_t1"

#define NAME1 "/sem_empty"
#define NAME2 "/sem_full"

#define handle_error(msg) \
           do { perror(msg); return EXIT_FAILURE; } while (0)
	

int main(int argc, char const *argv[]) {

	if(argc != 3) {
		printf("USAGE: %s N B\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	sem_t *empty;
	sem_t *full;

	int shmfd, err;
	
	const int n = atoi(argv[1]);
	const int b = atoi(argv[2]);
	
	struct shm_d* shmdata;
	const int BUFFER = atoi(argv[2]) + 1;
	
	if(b <= 0 || n <= 0) {
		handle_error("B and N need to be greater than 0\n");
	}
	
	
	struct shm_d {
	uint64_t ring_buf[BUFFER];
	uint64_t result;
	uint32_t in, out;
   };
  
  	sem_unlink(NAME1);
	sem_unlink(NAME2);

	pid_t pid;
	
	if((empty = sem_open(NAME1, O_CREAT | O_RDWR, 0666, BUFFER)) == SEM_FAILED) {
		handle_error("sem open failed");
	}
	
	if((full = sem_open(NAME2, O_CREAT | O_RDWR, 0666, 0)) == SEM_FAILED) {
		handle_error("sem open failed");
	}
	
	if((shmfd = shm_open(NAME,  O_CREAT | O_RDWR, 0666)) == -1) {
		handle_error("open failed");
	}
	
	if((err = ftruncate(shmfd, sizeof(*shmdata))) == -1) {
		handle_error("ftruncate failed");
	}
	
	shmdata = mmap(NULL, sizeof(*shmdata), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
	if(shmdata == MAP_FAILED) {
		handle_error("map");
	}
	
	shmdata->in = 0;
	shmdata->out = 0;
	
	if((pid = fork()) == -1) {
		handle_error("fork");
		}
	else if(pid == 0) {

		sem_open(NAME1, O_RDWR);
		sem_open(NAME2, O_RDWR);
		
		for(int i = 1; i <= n; i++) {
			sem_wait(empty);
			shmdata->ring_buf[shmdata->in] = i;
			shmdata->in = (shmdata->in + 1) % BUFFER;
			sem_post(full);
		}
		exit(EXIT_SUCCESS);
	}
	
	if((pid = fork()) == -1) {
		handle_error("fork");
		}
	else if(pid == 0) {
		uint64_t sums = 0;
		
		sem_open(NAME1, O_RDWR);
		sem_open(NAME2, O_RDWR);
		
		for(int i = 1; i <= n; i++) {
			sem_wait(full);
			sums += shmdata->ring_buf[shmdata->out];
			shmdata->out = (shmdata->out + 1) % BUFFER;
			sem_post(empty);
		}
		shmdata->result = sums;
		exit(EXIT_SUCCESS);
	}
	
	for(int i = 0; i < 2; i++) {
	wait(NULL);
	}
	
	printf("result: %ld\n", shmdata->result);
	shm_unlink(NAME);
	sem_unlink(NAME1);
	sem_unlink(NAME2);
	return EXIT_SUCCESS;
	
}

/* 
	task2 is much slower than task1
*/
