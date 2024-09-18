CC=g++
CFLAGS=-c

all: Ship.o Manager_of_ships.o Playground.o main.o
	$(CC) main.o Ship.o Manager_of_ships.o Playground.o -o oop

Ship.o: Ship.cpp
	$(CC) $(CFLAGS)  Ship.cpp

Manager_of_ships.o: Manager_of_ships.cpp
	$(CC) $(CFLAGS)  Manager_of_ships.cpp

Playground.o: Playground.cpp
	$(CC) $(CFLAGS)  Playground.cpp

main.o: main.cpp
	$(CC) $(CFLAGS)  main.cpp

clean:
	rm -rf *.o
	rm -rf oop.exe
	rm -rf oop