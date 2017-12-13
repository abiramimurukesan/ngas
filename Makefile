CC=gcc
FLAGS=-c -Wall
LIBS=-lm

test_ngas: ngas.o test_ngas.o
	$(CC) ngas.o test_ngas.o -lm -o test_ngas

ngas.o: ngas.c ngas.h
	$(CC) $(FLAGS) $(LIBS) ngas.c

test_ngas.o: test_ngas.c
	$(CC) $(FLAGS) $(LIBS) test_ngas.c

clean:
	rm *.o test_ngas
