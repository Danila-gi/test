CC=g++
CFLAGS=-c

all: Ship.o Manager_of_ships.o Playground.o Interface_of_abilities.o Interface_of_builders.o Double_atack.o Scanner.o Shelling.o \
Double_atack_builder.o Scanner_builder.o Shelling_builder.o Manager_of_abilities.o NoAbilitiesException.o ShipPlacmentException.o AtackException.o \
Add_ability.o Get_coords.o Ability_maker.o Paint.o Player.o Enemy.o Game.o main.o
	$(CC) main.o Ship.o Manager_of_ships.o Playground.o Interface_of_abilities.o Interface_of_builders.o Double_atack.o Scanner.o Shelling.o \
	 Double_atack_builder.o Scanner_builder.o Shelling_builder.o Manager_of_abilities.o NoAbilitiesException.o ShipPlacmentException.o AtackException.o \
	 Add_ability.o Get_coords.o Ability_maker.o Paint.o Player.o Enemy.o Game.o -o oop

Ship.o: includes/Ship.cpp
	$(CC) $(CFLAGS)  includes/Ship.cpp

Manager_of_ships.o: includes/Manager_of_ships.cpp
	$(CC) $(CFLAGS)  includes/Manager_of_ships.cpp

Playground.o: includes/Playground.cpp
	$(CC) $(CFLAGS)  includes/Playground.cpp

Interface_of_abilities.o: includes/Interface_of_abilities.cpp
	$(CC) $(CFLAGS)  includes/Interface_of_abilities.cpp

Interface_of_builders.o: includes/Interface_of_builders.cpp
	$(CC) $(CFLAGS)  includes/Interface_of_builders.cpp

Double_atack.o: includes/Double_atack.cpp
	$(CC) $(CFLAGS)  includes/Double_atack.cpp

Scanner.o: includes/Scanner.cpp
	$(CC) $(CFLAGS)  includes/Scanner.cpp

Shelling.o: includes/Shelling.cpp
	$(CC) $(CFLAGS)  includes/Shelling.cpp

Double_atack_builder.o: includes/Double_atack_builder.cpp
	$(CC) $(CFLAGS)  includes/Double_atack_builder.cpp

Scanner_builder.o: includes/Scanner_builder.cpp
	$(CC) $(CFLAGS)  includes/Scanner_builder.cpp

Shelling_builder.o: includes/Shelling_builder.cpp
	$(CC) $(CFLAGS)  includes/Shelling_builder.cpp

Manager_of_abilities.o: includes/Manager_of_abilities.cpp
	$(CC) $(CFLAGS)  includes/Manager_of_abilities.cpp

Add_ability.o: includes/Add_ability.cpp
	$(CC) $(CFLAGS)  includes/Add_ability.cpp

Get_coords.o: includes/Get_coords.cpp
	$(CC) $(CFLAGS)  includes/Get_coords.cpp

Ability_maker.o: includes/Ability_maker.cpp
	$(CC) $(CFLAGS)  includes/Ability_maker.cpp

NoAbilitiesException.o: includes/NoAbilitiesException.cpp
	$(CC) $(CFLAGS)  includes/NoAbilitiesException.cpp

ShipPlacmentException.o: includes/ShipPlacmentException.cpp
	$(CC) $(CFLAGS)  includes/ShipPlacmentException.cpp

AtackException.o: includes/AtackException.cpp
	$(CC) $(CFLAGS)  includes/AtackException.cpp

Paint.o: includes/Paint.cpp
	$(CC) $(CFLAGS)  includes/Paint.cpp

Player.o: includes/Player.cpp
	$(CC) $(CFLAGS)  includes/Player.cpp

Enemy.o: includes/Enemy.cpp
	$(CC) $(CFLAGS)  includes/Enemy.cpp

Game.o: includes/Game.cpp
	$(CC) $(CFLAGS)  includes/Game.cpp

main.o: main.cpp
	$(CC) $(CFLAGS)  main.cpp

clean:
	rm -rf *.o
	rm -rf oop.exe
	rm -rf oop