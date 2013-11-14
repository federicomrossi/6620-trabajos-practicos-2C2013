CC=gcc
FLAGS=-std=gnu99 -w
CLEAN=rm


all: gen

gen:
	gcc -g -c -w strcmpi.S -o strcmpi.o	
	gcc -g -c -w heap.S -o heap.o
	gcc -g -c -w heapsort.S -o heapsort.o
	gcc -g -c -w bubblesort.c -o bubblesort.o
	gcc -g -c -w tp1.c -o tp1.o
	gcc -g -w strcmpi.o heap.o heapsort.o bubblesort.o tp1.o -o tp1

tp1: bubblesort.o heapsort.o tp1.o
	$(CC) $(FLAGS) bubblesort.o heapsort.o tp1.o -o tp1

bubblesort.o: bubblesort.h bubblesort.c
	$(CC) $(FLAGS) -c bubblesort.c -o bubblesort.o

heapsort.o: heap.o heapsort.S
	$(CC) -c heapsort.S heap.o

heap.o:
	$(CC) -c heap.S strcmpi.o

strcmpi.o: heap.o strcmpi.S
	$(CC) -c strcmpi.S

clean:
	rm *.o tp1




