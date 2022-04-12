CFLAGS = -Wall -Wextra

all: read_my_env_var

read_my_env_var: read_my_env_var.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

read_my_env_var.o: read_my_env_var.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
clean:
	$(RM) read_my_env_var read_my_env_var.o
