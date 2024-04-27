#include <stdlib.h>
#include <math.h>
#include "struct.h"

void draw_circle(Rgb **arr, int coord_x, int coord_y, int color_r, int color_g, int color_b, int thickness, int H, int W){
	if (thickness % 2 == 1){
		int radius = (thickness - 1) / 2;
		int start_iteration_x = 0;
		int end_iteration_x = W;
		int start_iteration_y = 0;
		int end_iteration_y = H;
		if (coord_x - radius - 1 > 0)
			start_iteration_x = coord_x - radius - 1;
		if (coord_y - radius - 1 > 0)
			start_iteration_y = coord_y - radius - 1;
		if (coord_x + radius + 1 < W)
			end_iteration_x = coord_x + radius + 1;
		if (coord_y + radius + 1 < H)
			end_iteration_y = coord_y + radius + 1;
		for (int y = start_iteration_y; y < end_iteration_y; y++){
			for (int x = start_iteration_x; x < end_iteration_x; x++){
				if (y >= 0 && y < H){
					if (x >= 0 && x < W){
						int rast_from_center = (x - coord_x) * (x - coord_x) + (y - coord_y) * (y - coord_y);
						if (radius * radius >= rast_from_center){
							arr[H - 1 - y][x].r = color_r;
							arr[H - 1 - y][x].g = color_g;
							arr[H - 1 - y][x].b = color_b;
						}
					}
				}
			}
		}
	}
}


void draw_line(Rgb **arr, int start_x, int start_y, int end_x, int end_y, int color_r, int color_g, int color_b, int H, int W, int thickness){
    int len_of_line = sqrt((start_x - end_x) * (start_x - end_x) + (start_y - end_y) * (start_y - end_y));
    float offset_x = (float)(end_x - start_x) / (float)len_of_line;
    float offset_y = (float)(end_y - start_y) / (float)len_of_line;
	int coord_y, coord_x, distance_start, distance_end;
    for (int i = 0; i <= len_of_line; i++){
		coord_y = (int)(roundf(start_y + i * offset_y));
		coord_x = (int)(roundf(start_x + i * offset_x));
		if (thickness % 2 == 0){
			if (coord_y >= 0 && coord_y < H - 1){
				if (coord_x >= 0 && coord_x < W){
					arr[H - 1 - coord_y][coord_x].r = color_r;
					arr[H - 1 - coord_y][coord_x].g = color_g;
					arr[H - 1 - coord_y][coord_x].b = color_b;
					arr[H - 1 - coord_y - 1][coord_x].r = color_r;
					arr[H - 1 - coord_y - 1][coord_x].g = color_g;
					arr[H - 1 - coord_y - 1][coord_x].b = color_b;
				}
			}
			if (thickness > 1){
				draw_circle(arr, coord_x, coord_y, color_r, color_g, color_b, thickness - 1, H, W);
				draw_circle(arr, coord_x, coord_y - 1, color_r, color_g, color_b, thickness - 1, H, W);
			}
			continue;
		}
		if (coord_y >= 0 && coord_y < H){
			if (coord_x >= 0 && coord_x < W){
				arr[H - 1 - coord_y][coord_x].r = color_r;
				arr[H - 1 - coord_y][coord_x].g = color_g;
				arr[H - 1 - coord_y][coord_x].b = color_b;
			}
		}
		if (thickness > 1){
			draw_circle(arr, coord_x, coord_y, color_r, color_g, color_b, thickness, H, W);
		}
	}
}
