CC=g++
CFLAGS=-c -Wall -I./

all: lox

lox: main.o 
	$(CC) main.o -o lox

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o