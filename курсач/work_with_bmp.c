#include <stdio.h>
#include "struct.h"
#include <stdint.h>
#include <stdlib.h>

int isBMP(BitmapFileHeader bmfh, BitmapInfoHeader bmif){
	if (bmfh.signature != 0x4d42 || bmif.headerSize != 40 || bmif.bitsPerPixel != 24 || bmif.compression != 0){
        printf("This file is not for work with bmp\n");
        return 0;
    }
    return 1;
}

Rgb** readBMP(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, char* input_file){
	FILE *f = fopen(input_file, "rb");
	if (f == NULL){
		printf("incorrect filename");
		exit(42);
	}

	fread(bmfh, 1, sizeof(BitmapFileHeader), f);
	fread(bmif, 1, sizeof(BitmapInfoHeader), f);
	if (!isBMP(*bmfh, *bmif))
		exit(42);

	unsigned int H = bmif->height;
	unsigned int W = bmif->width;

	Rgb **arr = malloc(H * sizeof(Rgb*));
	if (arr == NULL){
		printf("Error with memory allocation\n");
		exit(1);
	}
	for(int i = 0; i < H; i++){
		arr[i] = malloc(W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4) % 4);
		if (arr[i] == NULL){
			printf("Error with memory allocation\n");
			exit(1);
		}
		fread(arr[i], 1, W * sizeof(Rgb) + (4 - (W * sizeof(Rgb)) % 4) % 4, f);
	}
	return arr;

}

void writeBMP(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, char* output_file, Rgb** arr){
	FILE *ff = fopen(output_file, "wb");

	int H = bmif->height;
	int W = bmif->width;
	fwrite(bmfh, sizeof(BitmapFileHeader), 1, ff);
	fwrite(bmif, sizeof(BitmapInfoHeader), 1, ff);
	int padding = (4 - (W * 3) % 4) % 4;
	uint8_t paddingBytes[3] = { 0 };
	for(int i = 0; i < H; i++){
		fwrite(arr[i], sizeof(Rgb), W, ff);
		fwrite(paddingBytes, sizeof(uint8_t), padding, ff);
	}
	fclose(ff);
}