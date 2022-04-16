#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSG_SIZE 128

int connection_socket;
void usage(char* name);
void* read_handler();
void* write_handler();
char buf[MSG_SIZE];
pthread_t tid_reader;
atomic_int kill = 0;

int main(int argc, char* argv[]) {

	if(argc != 3) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	pthread_t tid_writer;

	/* Create a socket for local connection */
	if((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return EXIT_FAILURE;
	}

	/* The sockaddr_in struct has some standard fields we don't need thus better freeing the
	 * struct */
	memset(&addr, 0, sizeof(struct sockaddr_in));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // on client

	/* Connect to the server */
	if(connect(connection_socket, (const struct sockaddr*)&addr, sizeof(struct sockaddr_in)) ==
	   -1) {
		perror("connect");
		return EXIT_FAILURE;
	}

	/* Send the initial message */
	if(write(connection_socket, argv[2], MSG_SIZE) == -1) {
		perror("write");
		return EXIT_FAILURE;
	}

	/* Start the writing thread and the reading thread */
	pthread_create(&tid_writer, NULL, write_handler, &argv[2]);
	pthread_create(&tid_reader, NULL, read_handler, NULL);

	pthread_join(tid_reader, NULL);
	pthread_join(tid_writer, NULL);

	close(connection_socket);

	return EXIT_SUCCESS;
}

void usage(char* name) {
	printf("USAGE: <%s> PORT USERNAME \n", name);
}

void* write_handler() {
	/* Busy waiting, write the other messages */

	while(1) {

		printf("\n> ");
		fgets(buf, sizeof(buf), stdin);

		if(write(connection_socket, buf, MSG_SIZE) == -1) {
			perror("write");
			return NULL;
		}

		if((strcmp(buf, "/quit\n") == 0) || strcmp(buf, "/shutdown\n") == 0) {
			kill = 1;
			break;
		}
	}
	pthread_cancel(tid_reader);
	return NULL;
}

void* read_handler() {
	while(1) {
		if(read(connection_socket, buf, MSG_SIZE) == -1) {
			perror("read");
			return NULL;
		}

		if(!kill) {
			printf("%s\n", buf);
		}
	}
	return NULL;
}