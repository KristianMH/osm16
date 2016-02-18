.PHONY: all clean valgrind quickgrind debug test

CC=gcc
CFLAGS=-Werror -Wextra -pedantic -std=c11 -g 

all: bouncer

bouncer: bouncer.c queue.c
	$(CC) $(CFLAGS) -o bouncer bouncer.c queue.c

clean:
	rm -f *.o
	rm -f bouncer

valgrind: bouncer
	valgrind --track-origins=yes --leak-check=full ./bouncer

quickgrind: bouncer
	cat input.txt | valgrind --track-origins=yes --leak-check=full ./bouncer

debug: input.txt gdb.script bouncer
	gdb -q -x gdb.script ./bouncer
test: bounce.py queue.c bouncer.c
	python3 bounce.py
