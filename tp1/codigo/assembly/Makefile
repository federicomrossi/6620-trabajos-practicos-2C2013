CC=gcc
FLAGS=-std=gnu99
CLEAN=rm


all: tp1

tp1: bubblesort.o heapsort.o tp1.o
	$(CC) $(FLAGS) bubblesort.o heapsort.o tp1.o -o tp1

tp1.o: bubblesort.o heapsort.o tp1.c
	$(CC) $(FLAGS) -c tp1.c -o tp1.o

bubblesort.o: bubblesort.h bubblesort.c
	$(CC) $(FLAGS) -c bubblesort.c -o bubblesort.o

heapsort.o: heapsort.h heapsort.c
	$(CC) $(FLAGS) -c heapsort.c -o heapsort.o
	
asm: 
	$(CC) -S tp1.c

clean:
	rm *.o tp1
