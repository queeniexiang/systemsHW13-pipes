all: pipes.o
	gcc -o test pipes.o

pipes.o: pipes.c
	gcc -c pipes.c

run: all
	./test

