#pragma once

int isBMP(BitmapFileHeader bmfh, BitmapInfoHeader bmif);
Rgb** readBMP(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, char* input_file);
void writeBMP(BitmapFileHeader* bmfh, BitmapInfoHeader* bmif, char* output_file, Rgb** arr);