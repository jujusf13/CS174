CC=g++
CFLAGS=-std=c++11 -g -Wall 

all: test playgame

game.o: game.cpp game.h properties.o player.o
	$(CC) $(CFLAGS) -c game.cpp

player.o: player.cpp player.h linkedlist.o
	$(CC) $(CFLAGS) -c player.cpp 

properties.o: properties.cpp properties.h linkedlist.o
	$(CC) $(CFLAGS) -c properties.cpp

test: game.o test.cpp 
	$(CC) $(CFLAGS) -o test player.o properties.o game.o test.cpp

playgame: game.o playgame.cpp
	$(CC) $(CFLAGS) -o playgame player.o properties.o playgame.cpp

linkedlist.o: linkedlist.cpp linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.cpp

clean:
	rm *.o test playgame