CC=gcc
FLAGS=-std=gnu99 -O0
CLEAN=rm


all: tp0

tp0: bubblesort.o shellsort.o fileloader.o tp0.o
	$(CC) $(FLAGS) bubblesort.o shellsort.o fileloader.o tp0.o -o tp0

tp0.o: bubblesort.h shellsort.h fileloader.h tp0.c
	$(CC) $(FLAGS) -c tp0.c -o tp0.o

bubblesort.o: bubblesort.h bubblesort.c
	$(CC) $(FLAGS) -c bubblesort.c -o bubblesort.o

shellsort.o: shellsort.h shellsort.c
	$(CC) $(FLAGS) -c shellsort.c -o shellsort.o

fileloader.o: fileloader.h fileloader.c
	$(CC) $(FLAGS) -c fileloader.c -o fileloader.o

clean:
	rm *.o tp0

valgrind1: 
	valgrind $(VGFLAGS) ./tp0 -s alice.txt

valgrind2: 
	valgrind $(VGFLAGS) ./tp0 -b alice.txt
