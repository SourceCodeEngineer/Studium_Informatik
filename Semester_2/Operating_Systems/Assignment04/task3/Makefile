CFLAGS = -Wall -Wextra

all: task3_client task3_server

task3_client: task3_client.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task3_client.o: task3_client.c 
	$(CC) $(CFLAGS) -c -o $@ $^
	
task3_server: task3_server.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task3_server.o: task3_server.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task3_client task3_client.o task3_server task3_server.o
