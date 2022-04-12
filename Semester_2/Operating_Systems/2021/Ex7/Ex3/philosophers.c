#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EAT_DURATION 100
#define NUM_PHILOSOPHER 5
#define EAT_ITERATIONS 1000
#define RIGHT_CHOPSTICK(n) (n)
#define LEFT_CHOPSTICK(n) (((n) + 1) % NUM_PHILOSOPHER)

pthread_t philosopher[NUM_PHILOSOPHER];
pthread_mutex_t chopstick[NUM_PHILOSOPHER];
pthread_mutex_t solution;
void* dine(void* id) {
	int n = (int)(intptr_t)id;
	for(int i = 0; i < EAT_ITERATIONS; ++i){
        pthread_mutex_lock(&solution);
		pthread_mutex_lock(&chopstick[RIGHT_CHOPSTICK(n)]);
		pthread_mutex_lock(&chopstick[LEFT_CHOPSTICK(n)]);
		pthread_mutex_unlock(&solution);
		usleep(EAT_DURATION);
		pthread_mutex_unlock(&chopstick[LEFT_CHOPSTICK(n)]);
		pthread_mutex_unlock(&chopstick[RIGHT_CHOPSTICK(n)]);
	}
	printf("Philosopher %d is done eating!\n", n);

	return NULL;
}

int main() {
        pthread_mutex_init(&solution, NULL);

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_mutex_init(&chopstick[i], NULL);
	}

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_create(&philosopher[i], NULL, dine, (void*)(intptr_t)i);
	}

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_join(philosopher[i], NULL);
	}

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_mutex_destroy(&chopstick[i]);
	}
        pthread_mutex_destroy(&solution);

	return EXIT_SUCCESS;
}

//das problem war, dass 2 philosopher immer vom selben die gabel genommen haben und so der dann keine gabel mehr hatte und er dann verhungert.

//In einem Betriebssystem tritt ein Deadlock auf, wenn ein Prozess oder Thread in einen Wartezustand eintritt,
//weil eine angeforderte Systemressource von einem anderen wartenden Prozess gehalten wird,
//der wiederum auf eine andere Ressource wartet, die von einem anderen wartenden Prozess gehalten wird.

//es passiert nicht immer aber wenn man es nicht regelt kann es auftreten muss es aber nicht.