CC=gcc
FLAGS=-std=gnu99
CLEAN=rm


all: tp0

tp0: pgm.o tp0.o
	$(CC) $(FLAGS) pgm.o tp0.o -o tp0

asm: 
	$(CC) -S tp0.c pgm.c

tp0.o: pgm.h tp0.c
	$(CC) $(FLAGS) -c tp0.c -o tp0.o

pgm.o: pgm.h pgm.c
	$(CC) $(FLAGS) -c pgm.c -o pgm.o

clean:
	rm *.o tp0
