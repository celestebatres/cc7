CC=gcc
CFLAGS=-I.

main: codigo1 codigo2

codigo1: codigo1.o codigo1_func.o
	$(CC) -o codigo1 codigo1.o codigo1_func.o

codigo2: codigo2.o codigo2_func.o
	$(CC)  -pthread  -o codigo2 codigo2.o codigo2_func.o


clean:
	rm -f *.o