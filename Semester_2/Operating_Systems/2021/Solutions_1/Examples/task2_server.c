#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSG_SIZE 128
#define MAX_CLIENTS 32

char buf[MSG_SIZE];
void usage(char* name);
void* listener(void* co_socket);
void* client_handler(void* cl_socket);
pthread_t ltid;
pthread_t client_threads[MAX_CLIENTS];
atomic_int active_clients = 0;
int client_sockets[MAX_CLIENTS];
char sep[] = ": ";

int main(int argc, char* argv[]) {

	if(argc != 2) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	int connection_socket;
	int ret_val;
	int port = atoi(argv[1]);

	/* Create a socket for local connection */
	if((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return EXIT_FAILURE;
	}

	/* The sockaddr_in struct has some standard fields we don't need thus better freeing the
	 * struct */
	memset(&addr, 0, sizeof(struct sockaddr_in));

	/* Bind the name, minus 1 due to the NULL terminating char */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // on server

	if((ret_val = bind(connection_socket, (const struct sockaddr*)&addr,
	                   sizeof(struct sockaddr_in)) == -1)) {

		if(errno == EADDRINUSE) {
			// Address is already in use
			printf("Address already in use!\n");
		} else {
			// Coul not bind the socket to the address
			perror("bind");
		}
		return EXIT_FAILURE;
	}

	/* Now spawn the listener thread */
	pthread_create(&ltid, NULL, listener, &connection_socket);
	pthread_join(ltid, NULL);

	printf("Server is shutting down. Waiting for %d clients to disconnect.\n", active_clients);

	/* Now wait for all clients to disconnect */
	for(int i = 0; i < MAX_CLIENTS; i++) {
		pthread_join(client_threads[i], NULL);
	}

	close(connection_socket);

	return EXIT_SUCCESS;
}

void usage(char* name) {
	printf("USAGE: <%s> PORT\n", name);
}

void* listener(void* co_socket) {
	int connection_socket = *(int*)co_socket;

	/* Now init the socket with the amount of the listeners, max 32 in our case */
	if(listen(connection_socket, MAX_CLIENTS) == -1) {
		perror("listen");
		return NULL;
	}

	/* Accept the connection from the clients, we expect max. 32 clients */
	for(int i = 0; i < MAX_CLIENTS; i++) {
		if((client_sockets[i] = accept(connection_socket, NULL, NULL)) == -1) {
			perror("accept");
			return NULL;
		}
		/* As a client connected create a client thread */
		pthread_create(&client_threads[i], NULL, client_handler, &client_sockets[i]);
		active_clients++;
	}
	return NULL;
}

void* client_handler(void* cl_socket) {
	/* Handle client message transfer */
	int client_socket = *(int*)cl_socket;
	char username[MSG_SIZE];

	if(read(client_socket, username, MSG_SIZE) == -1) {
		perror("read");
		return NULL;
	}

	printf("%s connected.\n\n", username);

	/* Read the first message from the client with the username */

	while(1) {
		/* Wait for the command to come in, note that we have to sync the access to the buf */
		if(read(client_socket, buf, MSG_SIZE) == -1) {
			perror("read");
			return NULL;
		}

		/* If the command is END close the connection */
		if((strcmp(buf, "/shutdown\n") == 0)) {
			printf("%s disconnected.\n\n", username);
			active_clients--;
			close(client_socket);
			pthread_cancel(ltid);
			break;
		}
		if(strcmp(buf, "/quit\n") == 0) {
			printf("%s disconnected.\n\n", username);
			active_clients--;
			close(client_socket);
			if(active_clients == 0) pthread_cancel(ltid);
			break;
		}
		/* Now send the message to all clients */
		for(int i = 0; i < active_clients; i++) {
			if(client_sockets[i] == client_socket) {
				continue;
			}
			/* Now compose the new String with the username */
			size_t len = strlen(buf) + strlen(username) + strlen(sep);
			char msg[len + 1]; // + null terminator
			strcpy(msg, username);
			strcat(msg, sep);
			strcat(msg, buf);

			if(write(client_sockets[i], msg, MSG_SIZE) == -1) {
				perror("write");
				return NULL;
			}
		}
	}
	return NULL;
}