#include <stdio.h>
#include "struct.h"

void print_help(){
	printf("--help, -h: get info, how to use programm\n");
	printf("--line -l: function of draw line\n");
	printf("--inverse_circle -I: fuction of invert color in circle\n");
	printf("--trim -t: function of cut part of image\n");
	printf("--starts, -s: coords, where function start draw line\n");
	printf("--end -e: coords, where function end draw line\n");
	printf("--color -c: choose color in format RGB\n");
	printf("--radius -r: input radius of circle in function 'inverese_circle'\n");
	printf("--center, -C: input ceneter coords of circle in function 'inverese_circle'\n");
	printf("--left_up -u: coords of top left of cut out image\n");
	printf("--right_down -d: coords of lower right of cut out image\n");
	printf("--thickness -T: thikness of line\n");
	printf("--input, -i: name of input bmp file\n");
	printf("--output -o: name of output bmp file\n");
	printf("--info: print info of bmp file\n");
}

void print_file_header(BitmapFileHeader header){
	printf("signature:\t%x (%hu)\n", header.signature,header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize,header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1,header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void print_info_header(BitmapInfoHeader header){
	printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
	printf("width: \t%x (%u)\n", header.width, header.width);
	printf("height: \t%x (%u)\n", header.height, header.height);
	printf("planes: \t%x (%hu)\n", header.planes, header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.imageSize,header.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
	printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}
