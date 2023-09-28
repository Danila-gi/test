all: menu

menu: menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o
	gcc menu.o index_first_negative.o index_last_negative.o sum_between_negative.o sum_before_and_after_negative.o -o menu

menu.o: menu.c
	gcc -c menu.c

index_first_negative.o: index_first_negative.c
	gcc -c index_first_negative.c

index_last_negative.o: index_last_negative.c
	gcc -c index_last_negative.c

sum_between_negative.o: sum_between_negative.c
	gcc -c sum_between_negative.c

sum_before_and_after_negative.o: sum_before_and_after_negative.c
	gcc -c sum_before_and_after_negative.c


clean:
	rm -rf *.o menu