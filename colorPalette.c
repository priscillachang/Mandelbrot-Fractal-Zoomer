/*********************
**  Color Palette generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"

//You don't need to call this function but it helps you understand how the arguments are passed in 
void usage(char* argv[])
{
	printf("Incorrect usage: Expected arguments are %s <inputfile> <outputfolder> <width> <heightpercolor>", argv[0]);
}

//Creates a color palette image for the given colorfile in outputfile. Width and heightpercolor dictates the dimensions of each color. Output should be in P3 format
int P3colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	if(colorfile == NULL || width == 0 || heightpercolor == 0) {
		return 1;
	}
	int colorcount;
	uint8_t** ref = FileToColorMap(colorfile, &colorcount);
	if(ref == NULL) {
		free(ref);
		return 1;
	}
	FILE* result = fopen(outputfile, "w");
	int vert_dim = heightpercolor * (colorcount);
	fprintf(result, "P3 %u %u 255\n", width, vert_dim);
	for(int i = 0; i < colorcount; i++) {
		for(int j = 0; j < heightpercolor; j++) {
			for(int p = 0; p < width; p++) {
				if (p < width - 1) {
					fprintf(result, "%d %d %d ", ref[i][0], ref[i][1], ref[i][2]);

				}
				else{
					fprintf(result, "%d %d %d\n", ref[i][0], ref[i][1], ref[i][2]);
				}
			}
		}
		free(ref[i]);
	}
	free(ref);
	fclose(result);
	return 0;
}

//Same as above, but with P6 format
int P6colorpalette(char* colorfile, int width, int heightpercolor, char* outputfile)
{
	if(colorfile == NULL || width == 0 || heightpercolor == 0) {
		return 1;
	}
	int colorcount;
	uint8_t** ref = FileToColorMap(colorfile, &colorcount);
	if(ref == NULL) {
		free(ref);
		return 1;
	}
	FILE* result = fopen(outputfile, "w+");
	int vert_dim = heightpercolor * (colorcount);
	fprintf(result, "P6 %u %u 255\n", width, vert_dim);
	for(int i = 0; i <colorcount; i++){
		for(int j = 0; j < heightpercolor * width; j++) {
			fwrite(ref[i], 1, 3, result);
		}
		free(ref[i]);
	}
	free(ref);
	fclose(result);
	return 0;
}


//The one piece of c code you don't have to read or understand. Still, might as well read it, if you have time.
int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		usage(argv);
		return 1;
	}
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	char* P3end = "/colorpaletteP3.ppm";
	char* P6end = "/colorpaletteP6.ppm";
	char buffer[strlen(argv[2]) + strlen(P3end)+1];
	sprintf(buffer, "%s%s", argv[2], P3end);
	int failed = P3colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P3colorpalette");
		return 1;
	}
	sprintf(buffer, "%s%s", argv[2], P6end);
	failed = P6colorpalette(argv[1], width, height, buffer);
	if (failed)
	{
		printf("Error in making P6colorpalette");
		return 1;
	}
	printf("P3colorpalette and P6colorpalette ran without error, output should be stored in %s%s, %s%s", argv[2], P3end, argv[2], P6end);
	return 0;
}




