#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdatomic.h> //module load gcc/9.2.0

#define BUF_SIZE 128
#define ClientSize 32

char buffer[BUF_SIZE];
pthread_t listenerThread;
pthread_t clients[ClientSize];
atomic_int current_clients = 0;
int sockfd[ClientSize];
char doublepoints[] = ": ";
int globalport;

void *clientThread(void *arg)
{
	int client_Socket = *(int *)arg;
	char name[BUF_SIZE];

	if (read(client_Socket, name, BUF_SIZE) == -1)
	{
		perror("read");
		return NULL;
	}

	printf("%s connected.\n\n", name);

	while (1)
	{
		if (read(client_Socket, buffer, BUF_SIZE) == -1)
		{
			perror("read");
			return NULL;
		}

		if ((strcmp(buffer, "/shutdown\n") == 0))
		{
			printf("%s disconnected.\n\n", name);
			current_clients--;
			printf("Server is shutting down. Waiting for %d clients to disconnect.\n", current_clients);
			if (current_clients == 0)
			{
				pthread_cancel(listenerThread);
				break;
			}
			break;
		}
		if (strcmp(buffer, "/quit\n") == 0)
		{
			printf("%s disconnected.\n\n", name);
			current_clients--;
			if (current_clients == 0)
			{
				pthread_cancel(listenerThread);
				break;
			}
			break;
		}
		for (int i = 0; i < current_clients; i++)
		{
			if (sockfd[i] == client_Socket)
			{
				continue;
			}

			size_t len = strlen(buffer) + strlen(name) + strlen(doublepoints);
			char clientmessage[len + 1]; // + null terminator
			strcpy(clientmessage, name);
			strcat(clientmessage, doublepoints);
			strcat(clientmessage, buffer);

			if (write(sockfd[i], clientmessage, BUF_SIZE) == -1)
			{
				perror("write");
				return NULL;
			}
		}
	}
	//close(client_Socket);
	return NULL;
}

void *listener(void *arg)
{
	int listenerSocket = *((int *)arg);

	if ((listen(listenerSocket, ClientSize)) == -1)
	{
		perror("Listen failed...\n");
		return NULL;
	}
	else
	{
		printf("Listening on port %d.\n", globalport);
	}
	for (int i = 0; i < ClientSize; i++)
	{
		if ((sockfd[i] = accept(listenerSocket, NULL, NULL)) == -1)
		{
			perror("accept");
			return NULL;
		}
		pthread_create(&clients[i], NULL, clientThread, &sockfd[i]);
		current_clients++;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("No argument passed through command line.\n");
		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	int port = atoi(argv[1]);
	int connfd;
	globalport = port;

	if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket creation failed...\n");
		return EXIT_FAILURE;
	}

	memset(&addr, 0, sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // on server
	//addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // on client

	if (bind(connfd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1)
	{
		perror("socket failed...\n");
		exit(0);
	}

	pthread_create(&listenerThread, NULL, listener, &connfd);
	pthread_join(listenerThread, NULL);

	for (int i = 0; i < ClientSize; i++)
	{
		pthread_join(clients[i], NULL);
		close(sockfd[i]);
		if (current_clients == 0)
		{
			break;
		}
	}

	close(connfd);

	return EXIT_SUCCESS;
}