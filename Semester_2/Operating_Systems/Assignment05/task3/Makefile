CFLAGS = -Wall -Wextra

all: task3_printer_server task3_printer

task3_printer_server: task3_printer_server.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task3_printer_server.o: task3_printer_server.c 
	$(CC) $(CFLAGS) -c -o $@ $^
	
task3_printer: task3_printer.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

task3_printer.o: task3_printer.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) task3_printer_server task3_printer_server.o task3_printer task3_printer.o