CC=gcc -Wall -O3

all: record_fplug

record_fplug: record_fplug.c
	$(CC) -o $@ $^

.c.o:
	$(CC) -o $@ -c $^

clean:
	rm -r record_fplug
