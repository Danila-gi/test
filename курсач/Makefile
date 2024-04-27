CC=gcc
CFLAGS=-c -std=c11

all: main.o function_of_draw_line.o function_of_invert_color.o function_of_cut_part.o print_info_programm_img.o work_with_bmp.o
	$(CC) main.o function_of_draw_line.o function_of_invert_color.o function_of_cut_part.o print_info_programm_img.o work_with_bmp.o -o cw -lm

main.o: main.c
	$(CC) $(CFLAGS)  main.c

function_of_draw_line.o: function_of_draw_line.h
	$(CC) $(CFLAGS)  function_of_draw_line.c -lm

function_of_invert_color.o: function_of_invert_color.h
	$(CC) $(CFLAGS) function_of_invert_color.c

function_of_cut_part.o: function_of_cut_part.h
	$(CC) $(CFLAGS) function_of_cut_part.c

print_info_programm_img.o: print_info_programm_img.h
	$(CC) $(CFLAGS) print_info_programm_img.c

work_with_bmp.o: work_with_bmp.h
	$(CC) $(CFLAGS) work_with_bmp.c


clean:
	rm -rf *.o
	rm -rf cw.exe
	rm -rf cw