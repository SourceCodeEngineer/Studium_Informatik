#include "myqueue.h"
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

#define NUMBER_OF_JOBS 50 * 1000

typedef struct {
  size_t size;
  int number_of_pending_jobs;
  bool shutdown;
  pthread_t *threads;
  myqueue *pending_jobs;
  pthread_mutex_t *access_pending_jobs;
  pthread_cond_t *new_job_available;
} thread_pool;

void pool_create(thread_pool *pool, size_t size);
void *start_routine(void *arg);
job_id pool_submit(thread_pool *pool, job_function start_routine, job_arg arg);
void free_job(job_id job);
void pool_await(job_id job);
void free_queue(myqueue *queue);
void pool_destroy(thread_pool *pool);

void pool_create(thread_pool *pool, size_t size) {
  /* Initializing pool struct */
  pool->shutdown = false;
  pool->size = size;
  pool->number_of_pending_jobs = 0;
  pthread_t *threads = malloc(size * sizeof(pthread_t));
  pool->threads = threads;

  // logic for incoming jobs
  myqueue *pending_jobs = malloc(sizeof(myqueue));
  myqueue_init(pending_jobs);
  pool->pending_jobs = pending_jobs;

  pthread_mutex_t *access_pending_jobs = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(access_pending_jobs, NULL);
  pool->access_pending_jobs = access_pending_jobs;

  pthread_cond_t *new_job_available = malloc(sizeof(pthread_cond_t));
  pthread_cond_init(new_job_available, NULL);
  pool->new_job_available = new_job_available;

  /* Starting size amount of threads */
  for (size_t i = 0; i < size; ++i) {
    if (pthread_create(&threads[i], NULL, &start_routine, pool) != 0) {
      perror("pthread_create\n");
      exit(EXIT_FAILURE);
    }
  }
}

job_id pool_submit(thread_pool *pool, job_function start_routine, job_arg arg) {
  /* Creating news job */
  job_id new_job = malloc(sizeof(job));
  new_job->function = start_routine;
  new_job->arg = arg;

  new_job->job_mutex = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(new_job->job_mutex, NULL);

  new_job->job_has_finished = false;

  new_job->job_finished = malloc(sizeof(pthread_cond_t));
  pthread_cond_init(new_job->job_finished, NULL);

  /* Add job to pending_jobs */
  pthread_mutex_lock(pool->access_pending_jobs);
  myqueue_push(pool->pending_jobs, new_job);
  pool->number_of_pending_jobs++;
  pthread_mutex_unlock(pool->access_pending_jobs);

  /* Signal new_job_available */
  pthread_cond_signal(pool->new_job_available);
  return new_job;
}

void free_job(job_id job) {
  /* Free all memory allocated for the job */
  free(job->job_mutex);
  free(job->job_finished);
  free(job);
}

void pool_await(job_id job) {
  /* Setup */
  pthread_mutex_t *job_mutex = job->job_mutex;

  /* Wait for job to finish */
  pthread_mutex_lock(job_mutex);
  while (!job->job_has_finished) {
    pthread_cond_wait(job->job_finished, job_mutex);
  }
  pthread_mutex_unlock(job_mutex);

  /* Free job memory */
  free_job(job);

  /* Controlflow can continue */
  return;
}

void free_queue(myqueue *queue) {
  while (!myqueue_is_empty(queue)) {
    job_id job = myqueue_pop(queue);
    free_job(job);
  }
  free(queue);
  return;
}

void pool_destroy(thread_pool *pool) {
  /* Set shutdown flag */
  pool->shutdown = true;

  /* Ensure every thread wakes up to check the shutdown flag */

  /* If there are no more jobs pending in the queue every thread will wait
   * for a new job to arrive.
   * In order for them to check the shutdown flag they have to wake up
   * So we just signal the condition for every thread that is waiting
   * for the condition at the time the shutdown is initiated
   */
  for (size_t i = 0; i < pool->size - pool->number_of_pending_jobs; ++i) {
    pthread_cond_signal(pool->new_job_available);
  }

  /* Joining all worker threads after they checked the shutdown flag */
  pthread_t *threads = pool->threads;
  for (size_t i = 0; i < pool->size; ++i) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join\n");
      exit(EXIT_FAILURE);
    }
  }

  /* Cleanup */
  free(pool->threads);
  pthread_mutex_lock(pool->access_pending_jobs);
  free_queue(pool->pending_jobs);
  pthread_mutex_unlock(pool->access_pending_jobs);
  free(pool->access_pending_jobs);
  free(pool->new_job_available);
  free(pool);
  return;
}

void *start_routine(void *arg) {
  /* Setup */
  thread_pool *pool = arg;
  myqueue *pending_jobs = pool->pending_jobs;
  pthread_mutex_t *access_pending_jobs = pool->access_pending_jobs;
  pthread_cond_t *new_job_available = pool->new_job_available;
  
  /* Waiting for job */
  while (!pool->shutdown) {
    pthread_mutex_lock(access_pending_jobs);
    while (!pool->shutdown && myqueue_is_empty(pending_jobs)) {
      pthread_cond_wait(new_job_available, access_pending_jobs);
    }
    if (pool->shutdown) {
      break;
    }

    /* Get job */
    job *job = myqueue_pop(pending_jobs);
    pool->number_of_pending_jobs--;
    pthread_mutex_unlock(access_pending_jobs);

    /* Setup job */
    job_function function = *job->function;
    job_arg arg = job->arg;
    pthread_mutex_t *job_mutex = job->job_mutex;
    pthread_cond_t *job_finished = job->job_finished;

    /* Execute job */
    function(arg);

    /* Signal job_finshed */
    pthread_mutex_lock(job_mutex);
    job->job_has_finished = true;
    pthread_mutex_unlock(job_mutex);
    pthread_cond_signal(job_finished);

    /* Loop and check for shutdown/new job */
  }
  // shutdown = true
  /* Shutdown */
  pthread_mutex_unlock(access_pending_jobs);
  pthread_exit(EXIT_SUCCESS);
}
