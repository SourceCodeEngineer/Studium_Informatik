CFLAGS = -Wall -Wextra

all: ls_grep_wc ls_wc

ls_grep_wc: ls_grep_wc.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

ls_grep_wc.o: ls_grep_wc.c 
	$(CC) $(CFLAGS) -c -o $@ $^
	
ls_wc: ls_wc.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

ls_wc.o: ls_wc.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) ls_grep_wc ls_grep_wc.o ls_wc ls_wc.o
