#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <assert.h>
#include <string.h>

#define ARRAY_INIT_CAPACITY 4

#define MAX 256
#define MAX_CLIENTS 32
#define SA struct sockaddr
#define ACTIVE 0
#define TERM 1
#define LEFT 2

typedef struct client
{
	int *id;
	char (*name)[MAX];
	_Atomic pthread_t cThread;
	_Atomic int socket;
	_Atomic int status;
} client_t;

_Atomic int shd = 0;
client_t clients[MAX_CLIENTS];
_Atomic int cclients = 0;
pthread_t listenThread;

void *client(void *sockfd)
{
	int *id = (int *)sockfd;
	char buff[MAX];
	char(*name)[MAX] = clients[*id].name;
	int ret;
	while ((ret = recv(clients[*id].socket, buff, sizeof(buff), 0)) > 0)
	{
		if (strncmp(buff, "/quit", 5) == 0)
		{
			printf("%s disconnected\n", *name);
			clients[*id].status = TERM;
			close(clients[*id].socket);
			break;
		}
		else if (strncmp("/shutdown", buff, 9) == 0)
		{
			printf("%s disconnected\n", *name);
			clients[*id].status = TERM;
			close(clients[*id].socket);
			shd = 1;
			pthread_cancel(listenThread);
			break;
		}
		else
		{
			char(*msg)[MAX] = malloc(MAX * sizeof(char));
			strcat(*msg, *name);
			strcat(*msg, ": ");
			strcat(*msg, buff);
			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				if (i != *id && clients[i].status == ACTIVE && *clients[i].name != NULL)
				{
					if (send(clients[i].socket, msg, MAX, 0) < 0)
					{
						perror("write failed");
						exit(EXIT_FAILURE);
					}
				}
			}
			free(msg);
		}
		bzero(buff, MAX);
	}

	free(clients[*id].name);
	free(id);
	return NULL;
}

void *listener(void *sockfd)
{

	int *sSocket = (int *)sockfd;
	if (listen(*sSocket, 1) != 0)
	{
		printf("Listen failed...\n");
		exit(EXIT_FAILURE);
	}
	printf("Server listening\n");

	while (!shd)
	{
		int len = sizeof(struct sockaddr_in);
		struct sockaddr_in cli;

		int connfd = accept(*sSocket, (SA *)&cli, (socklen_t *)&len);
		if (connfd < 0)
		{
			printf("server acccept failed...\n");
			exit(EXIT_FAILURE);
		}
		int *id = malloc(sizeof(int));
		*id = cclients;

		char(*cName)[MAX] = malloc(MAX * sizeof(char));
		if (recv(connfd, *cName, MAX, 0) <= 0)
		{
			perror("Client Name failed");
			exit(EXIT_FAILURE);
		}

		pthread_t cThread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int ret = pthread_create(&cThread, &attr, &client, id);
		if (ret != 0)
		{
			perror("Thread failed");
			exit(EXIT_FAILURE);
		}

		client_t currClient = {id, cName, cThread, connfd, ACTIVE};
		clients[*id] = currClient;
		cclients++;
		printf("%s connected; %d total clients\n", *cName, cclients);
	}
	return NULL;
}

typedef struct array
{
	void **items;
	size_t capacity;
	size_t size;
} my_array;

void *my_array_init()
{
	my_array *array = malloc(sizeof(*array));
	if (!array)
	{
		return NULL;
	}
	array->capacity = ARRAY_INIT_CAPACITY;
	array->size = 0;
	array->items = malloc(sizeof(void *) * array->capacity);
	if (!array->items)
	{
		free(array);
		return NULL;
	}
	return array;
}

size_t my_array_size(my_array *array)
{
	assert(array);
	return array->size;
}

static int array_resize(my_array *array, size_t capacity)
{
	assert(array);
	void **items = realloc(array->items, sizeof(*items) * capacity);
	if (!items)
	{
		return -1;
	}
	array->items = items;
	array->capacity = capacity;
	return 0;
}

void my_array_push_back(my_array *array, void *item)
{
	assert(array);
	if (array->capacity == array->size)
		array_resize(array, array->capacity * 2);
	array->items[array->size++] = item;
}

void *my_array_get(my_array *array, size_t idx)
{
	assert(array);
	if (idx < array->size)
		return array->items[idx];
	return NULL;
}

void my_array_delete(my_array *array, size_t idx)
{
	assert(array);
	if (idx >= array->size)
		return;

	memmove(array->items + idx, array->items + (idx + 1),
			sizeof(*array->items) * (array->size - (idx + 1)));
	--array->size;

	if (array->size > 0 && array->size == array->capacity / 4)
		array_resize(array, array->capacity / 2);
}

void my_array_free(my_array *array)
{
	assert(array);
	free(array->items);
	free(array);
}

void *my_array_front(my_array *array)
{
	return my_array_get(array, 0);
}

void *my_array_pop_front(my_array *array)
{
	assert(array);
	void *data = my_array_front(array);
	my_array_delete(array, 0);
	return data;
}

int main(int argc, char **argv)
{

	if (argc != 2)
	{
		printf("Usage: %s port", argv[0]);
		return EXIT_FAILURE;
	}
	memset(clients, 0, MAX_CLIENTS * sizeof(clients[0]));
	int listenfd;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(strtol(argv[1], NULL, 10));

	htons(strtol(argv[1], NULL, 10));

	if ((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
	{
		printf("socket bind failed...\n");
		return EXIT_FAILURE;
	}

	int ret = pthread_create(&listenThread, NULL, &listener, &listenfd);
	if (ret != 0)
	{
		perror("thread failed");
		return EXIT_FAILURE;
	}

	ret = pthread_join(listenThread, NULL);
	if (ret != 0)
	{
		perror("join failed");
		return EXIT_FAILURE;
	}

	printf("Server is shutting down! Waiting for %d clients to disconnect.\n", cclients - 1);
	while (cclients > 0)
	{
		pthread_t currDc;
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (clients[i].status == TERM)
			{
				currDc = clients[i].cThread;
				clients[i].status = LEFT;
				pthread_join(currDc, NULL);
				cclients--;
			}
		}
	}
	printf("All clients disconnected, cleaning up and shutting down!\n");
	close(listenfd);
	return EXIT_SUCCESS;
}
