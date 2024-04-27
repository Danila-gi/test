#include <stdlib.h>
#include "struct.h"

Rgb ** cut_of_picture(Rgb **arr, BitmapInfoHeader * bmif, int left_up_x, int left_up_y, int right_down_x, int right_down_y, int H, int W){
	int size_y = right_down_y - left_up_y;
	int size_x = right_down_x - left_up_x;
	Rgb ** new_arr = malloc(size_y * sizeof(Rgb *));
	for (int i = 0; i < size_y; i++){
		new_arr[i] = malloc(size_x * sizeof(Rgb) + (size_x * 3) % 4);
	}
	for (int i = 0; i < size_y; i++){
		for (int j = 0; j < size_x; j++){
			if (i >= 0 && j >= 0 && j < W && H - 1 - left_up_y - i >= 0 && H - 1 - left_up_y - i < H && left_up_x + j >= 0 && left_up_x + j < W){
				new_arr[size_y - i - 1][j] = arr[H - 1 - left_up_y - i][left_up_x + j];
			}
		}
	}
	bmif->height = size_y;
	bmif->width = size_x;
	return new_arr;
}