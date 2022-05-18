// worked together in a colaboration with csaz7620, csaz2055, csaz7804

#include "myqueue.h"
#include "threadpool.h" // threadpool implementation

#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MESSAGE_SIZE 4096

#define ERROR(message)   \
  do                     \
  {                      \
    perror(message);     \
    return EXIT_FAILURE; \
  } while (0)

#define CHECK_STRTOL(errno, endptr, strptr, message)       \
  do                                                       \
  {                                                        \
    if (errno != 0 || *endptr != '\0' || endptr == strptr) \
    {                                                      \
      ERROR(message);                                      \
    }                                                      \
  } while (0)

typedef struct
{
  int sockfd;
  struct sockaddr *addr;
  pthread_t *listener_thread;
} listener_args;

typedef struct
{
  int connectionfd;
  pthread_t *listener_thread;
} handler_args;

void connection_handler(job_arg arg);
void *listener_routine(void *arg);

int main(int argc, char *argv[])
{
  /* Input */
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s PORT", argv[0]);
    return EXIT_FAILURE;
  }
  char *endptr;
  errno = 0;
  int port = strtol(argv[1], &endptr, 10); // converting port string to int
  CHECK_STRTOL(errno, endptr, argv[1], "strtol port");

  /* Create socket */
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd <= 0)
  {
    /* Cleanup */
    close(sockfd);
    ERROR("creating socket");
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(struct sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* Bind socket */
  if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) != 0)
  {
    /* Cleanup */
    close(sockfd);
    ERROR("bind socket\n");
  }

  /* Start listener thread */
  pthread_t listener_thread;
  listener_args arg;
  arg.sockfd = sockfd;
  arg.addr = (struct sockaddr *)&addr;
  arg.listener_thread = &listener_thread;

  if (pthread_create(&listener_thread, NULL, &listener_routine, &arg))
  {
    ERROR("pthread_create listener");
  }
  printf("Listening on port %d.\n", port);

  /* Join listener thread on shutdown */
  if (pthread_join(listener_thread, NULL))
  {
    ERROR("pthread_join listener");
  }
  printf("Shutting down.\n");
  /* Cleanup */
  close(sockfd);
  return EXIT_SUCCESS;
}

void *listener_routine(void *arg)
{
  /* Setup */
  listener_args *args = arg;
  int sockfd = args->sockfd;
  /* Create thread pool */
  thread_pool pool;
  pool_create(&pool, 4);

  /* Start listening */
  if (listen(sockfd, 5) != 0)
  {
    /* Cleanup */
    close(sockfd);
    pool_destroy(&pool);
    perror("socket listen");
    pthread_exit(NULL);
  }

  /* Accept requests and add them to thread pool */
  while (true)
  {
    /* Connect to client */
    socklen_t addrlen = sizeof(*args->addr);
    int connectionfd = accept(sockfd, args->addr, &addrlen);
    if (connectionfd <= 0)
    {
      /* Cleanup */
      close(connectionfd);
      close(sockfd);
      pool_destroy(&pool);
      perror("socket accept");
      pthread_exit(NULL);
    }
    handler_args *harg = malloc(sizeof(handler_args));
    harg->connectionfd = connectionfd;
    harg->listener_thread = args->listener_thread;
    pool_submit(&pool, &connection_handler, harg);
  }
  pool_destroy(&pool);
  pthread_exit(NULL);
}

void connection_handler(job_arg arg)
{
  /* Setup */
  handler_args *args = arg;
  int connectionfd = args->connectionfd;
  pthread_t *listener_thread = args->listener_thread;
  free(args);

  char message[MESSAGE_SIZE] = {0};
  char Http_return[] = "HTTP/1.1 200 OK\r\n"
                       "Content-Type: text/html\r\n"
                       "Content-Length: 10\r\n\r\n"
                       "YIKES";
  /* Simulate workload */
  usleep(100 * 1000);

  /* Read from Client */
  bzero(message, MESSAGE_SIZE); // clean previous message
  int read_ret = read(connectionfd, &message, MESSAGE_SIZE - 1);
  if (read_ret < 0)
  {
    /* Cleanup */
    close(connectionfd);
    pthread_cancel(*listener_thread);
    pthread_exit(NULL);
  }

  /* Check for shutdown request */
  if (strncmp("GET /shutdown", message, 13) == 0)
  {
    /* Cleanup */
    close(connectionfd);
    pthread_cancel(*listener_thread);
    pthread_exit(NULL);
  }

  /* Write to client */
  dprintf(connectionfd, "%s", Http_return);

  /* Exit */
  close(connectionfd);
  pthread_exit(EXIT_SUCCESS);
}
