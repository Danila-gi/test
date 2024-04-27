#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include "struct.h"
#include <string.h>
#include <stdint.h>
#include "function_of_draw_line.h"
#include "function_of_invert_color.h"
#include "function_of_cut_part.h"
#include "print_info_programm_img.h"
#include "work_with_bmp.h"

int* get_arguments(char* str, int count_of_argumets){
	char *pch = strtok(str, ".");
	int i = 0;
	int* arr = malloc(3 * sizeof(int));
	while (pch != NULL){
		arr[i++] = atoi(pch);
		pch = strtok(NULL, ".");
	}
	if (i == count_of_argumets)
		return arr;
	printf("incorrect format of arguments");
	exit(41);
}

int main(int argc, char *argv[]){
	puts("Course work for option 4.6, created by Danila Ivanov");
	char* input_file = argv[argc - 1];
	const char* short_options = "hlIts:e:c:C:r:u:d:T:i:o:";

	const struct option long_options[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "line", no_argument, NULL, 'l' },
		{ "inverse_circle", no_argument, NULL, 'I' },
		{ "trim", no_argument, NULL, 't' },
        { "start", required_argument, NULL, 's' },
		{ "end", required_argument, NULL, 'e' },
		{ "color", required_argument, NULL, 'c' },
        { "radius", required_argument, NULL, 'r' },
		{ "center", required_argument, NULL, 'C' },
        { "left_up", required_argument, NULL, 'u' },
		{ "right_down", required_argument, NULL, 'd' },
		{ "thickness", required_argument, NULL, 'T' },
		{ "input", required_argument, NULL, 'i' },
		{ "output", required_argument, NULL, 'o' },
		{ "info", no_argument, NULL, 0},
		{ NULL, 0, NULL, 0 }
	};

	int rez;
	int option_index;

	int option = -1;
    char *start = NULL;
    char *end = NULL;
    char *color = NULL;
    int thickness = 0;
    char *center = NULL;
    int radius = 0;
    char *left_up = NULL;
    char *right_down = NULL;
	char* output_file = NULL;

	while ((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1){
        switch(rez){
			case 'h': {
				print_help();
				exit(0);
				break;
			};
			case 'l': {
				option = 1;
				break;
			};
	
			case 'I': {
				option = 2;
				break;
			};
			case 't': {
				option = 3;
				break;
			}
			case 's': {
				start = optarg;
				break;
			}
			case 'e': {
				end = optarg;
				break;
			}
			case 'c': {
				color = optarg;
				break;
			}
			case 'T': {
				thickness = atoi(optarg);
				break;
			}
			case 'C': {
				center = optarg;
				break;
			}
			case 'r': {
				radius = atoi(optarg);
				break;
			}
			case 'u': {
				left_up = optarg;
				break;
			}
			case 'd': {
				right_down = optarg;
				break;
			}
			case 'i': {
				input_file = optarg;
				break;
			}
			case 'o': {
				output_file = optarg;
				break;
			}
			case 0:{
				if (strcmp(long_options[option_index].name, "info") == 0){
                    option = 4;
                } else {
                    printf("found unknown option\n");
					exit(43);
                }
				break;
			}
			case '?': default: {
				printf("found unknown option\n");
				exit(43);
				break;
			};
		};
	};

	if (strcmp(input_file, output_file) == 0){
		printf("files have same names");
		exit(42);
	}

	BitmapFileHeader bmfh;
	BitmapInfoHeader bmif;
	Rgb** arr = readBMP(&bmfh, &bmif, input_file);

	switch (option)
	{
		case 1:{
			int* start_arr = get_arguments(start, 2);
			int* end_arr = get_arguments(end, 2);
			int* color_arr = get_arguments(color, 3);
			if (!(0 <= color_arr[0] && color_arr[0] <= 255 && 0 <= color_arr[1] && color_arr[1] <= 255 && 0 <= color_arr[2] && color_arr[2] <= 255)){
				printf("incorrect color\n");
				exit(40);
			}
			draw_line(arr, start_arr[0], start_arr[1], end_arr[0], end_arr[1], color_arr[0], color_arr[1], color_arr[2], bmif.height, bmif.width, thickness);
			break;
		};
		
		case 2:{
			int* center_arr = get_arguments(center, 2);
			invert_colors(arr, center_arr[0], center_arr[1], radius, bmif.height, bmif.width);
			break;
		};

		case 3:{
			int* left_up_arr = get_arguments(left_up, 2);
			int* right_down_arr = get_arguments(right_down, 2);
			if (left_up_arr[0] > right_down_arr[0] || left_up_arr[1] > right_down_arr[1]){
				printf("Incorrect coords!\n");
				exit(41);
			}
			if (left_up_arr[0] >= 0 && left_up_arr[1] >= 0)
				arr = cut_of_picture(arr, &bmif, left_up_arr[0], left_up_arr[1], right_down_arr[0], right_down_arr[1], bmif.height, bmif.width);
			break;
		};

		case 4:{
			print_file_header(bmfh);
			print_info_header(bmif);
			exit(0);
		};
		
		default:
			break;
	}

	writeBMP(&bmfh, &bmif, output_file, arr);

	return 0;
}