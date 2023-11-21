CC=gcc
CFLAGS=-c -std=c11

all: main.o reading.o delete.o memory.o function_1.o function_2.o function_3.o function_4.o
	$(CC) main.o reading.o delete.o memory.o function_1.o function_2.o function_3.o function_4.o -o cw

main.o: main.c reading.h
	$(CC) $(CFLAGS)  main.c

reading.o: reading.h
	$(CC) $(CFLAGS) reading.c

delete.o: delete.h
	$(CC) $(CFLAGS) delete.c

memory.o: memory.h
	$(CC) $(CFLAGS) memory.c

function_1.o: function_1.h
	$(CC) $(CFLAGS) function_1.c

function_2.o: function_2.h
	$(CC) $(CFLAGS) function_2.c

function_3.o: function_3.h
	$(CC) $(CFLAGS) function_3.c

function_4.o: function_4.h
	$(CC) $(CFLAGS) function_4.c

clean:
	rm -rf *.o
	rm -rf cw.exe
	rm -rf cw