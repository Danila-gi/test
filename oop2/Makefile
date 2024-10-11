CC=g++
CFLAGS=-c

all: Ship.o Manager_of_ships.o Playground.o Double_atack.o Scanner.o Shelling.o main.o
	$(CC) main.o Ship.o Manager_of_ships.o Playground.o Double_atack.o Scanner.o Shelling.o -o oop

Ship.o: includes/Ship.cpp
	$(CC) $(CFLAGS)  includes/Ship.cpp

Manager_of_ships.o: includes/Manager_of_ships.cpp
	$(CC) $(CFLAGS)  includes/Manager_of_ships.cpp

Playground.o: includes/Playground.cpp
	$(CC) $(CFLAGS)  includes/Playground.cpp

Double_atack.o: includes/Double_atack.cpp
	$(CC) $(CFLAGS)  includes/Double_atack.cpp

Scanner.o: includes/Scanner.cpp
	$(CC) $(CFLAGS)  includes/Scanner.cpp

Shelling.o: includes/Shelling.cpp
	$(CC) $(CFLAGS)  includes/Shelling.cpp

main.o: main.cpp
	$(CC) $(CFLAGS)  main.cpp

clean:
	rm -rf *.o
	rm -rf oop.exe
	rm -rf oop