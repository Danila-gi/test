#include <stdlib.h>
#include "struct.h"

void invert_colors(Rgb **arr, int center_x, int center_y, int radius, int H, int W){
	for (int y = 1; y < H; y++){
		for (int x = 0; x < W; x++){
			int rast_from_center = (x - center_x) * (x - center_x) + (y - center_y) * (y - center_y);
			if (radius * radius >= rast_from_center){
				arr[H - y][x].r = 255 - arr[H - y][x].r;
				arr[H - y][x].g = 255 - arr[H - y][x].g;
				arr[H - y][x].b = 255 - arr[H - y][x].b;
			}
		}
	}
}