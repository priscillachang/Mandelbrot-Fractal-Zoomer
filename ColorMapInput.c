/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
	FILE* read = fopen(colorfile, "r");
	if (read == NULL) {
		return NULL;
	}
	int color_num;
	if(!fscanf(read, "%d", &color_num)) {
		fclose(read);
		return NULL;
	}
	*colorcount = color_num;
	uint8_t** color_array = (uint8_t**) malloc(color_num * sizeof(uint8_t*));
	int a=0, b=0, c=0;
	int i =0;
	for( i = 0; i < color_num && fscanf(read, "%d %d %d", &a, &b, &c) == 3; i++) {
		uint8_t* mini_array = (uint8_t*) malloc(3*sizeof(uint8_t));
		//color_array[i] = (uint8_t*) malloc(3 * sizeof(uint8_t));
		/*if(!fscanf(read, "%d%d%d", &a, &b, &c)){
			for(int j = 0; j < i; j++) {
				free(color_array[j]);
			}
			free(mini_array);
			free(color_array);
			fclose(read);
			return NULL;
		}*/
		//printf("%d %d %d ", a, b, c);
		if (a<0 || b<0 || c<0 || a>255 || b>255 || c>255){
			for(int j = 0; j < i; j++) {
				free(color_array[j]);
			}
			free(color_array);
			free(mini_array);
			fclose(read);
			printf("%d %d %d ", a, b, c);
			printf("asdf3");
			return NULL;
		} 
		mini_array[0] = a;
		mini_array[1] = b;
		mini_array[2] = c;
		/*color_array[i][0] = a;
		color_array[i][1] = b;
		color_array[i][2] = c;*/
		color_array[i] = mini_array;
	}

	if(i != color_num) {
			for(int j = 0; j < i; j++) {
				free(color_array[j]);
				}
				free(color_array);
				fclose(read);
				printf("asdf4");
				return NULL;
		}
	fclose(read);
	
	return color_array;
}


