CFLAGS = -Wall -Wextra

all: server client

server: server.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lrt

server.o: server.c 
	$(CC) $(CFLAGS) -c -o $@ $^ 
	
client: client.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -lrt

client.o: client.c 
	$(CC) $(CFLAGS) -c -o $@ $^ 

clean:
	$(RM) server server.o client client.o