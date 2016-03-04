.PHONY: all clean valgrind quickgrind debug testfile

CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11 -g

all: bouncer

bouncer: queue.o bouncer.c
	$(CC) $(CFLAGS) -pthread -o bouncer queue.o bouncer.c

queue.o: queue.c
	$(CC) $(CFLAGS) -pthread -c  queue.c

clean:
	rm -f *.o
	rm -f bouncer
	rm -f queuetest

valgrind: bouncer
	valgrind --track-origins=yes --leak-check=full ./bouncer

quickgrind: bouncer
	cat input.txt | valgrind --track-origins=yes --leak-check=full ./bouncer

debug: input.txt gdb.script bouncer
	gdb -q -x gdb.script ./bouncer

test: queuetest.c queue.o
	$(CC) $(CFLAGS) -pthread -o queuetest queue.o queuetest.c
	./queuetest
