/*********************
**  Mandelbrot fractal movie generator
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include <sys/types.h>

void printUsage(char* argv[])
{
  printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
  printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so 
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, u_int64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, u_int64_t resolution, u_int64_t ** output){
    for(int i = 0; i < framecount; i++) {
    	Mandelbrot(threshold, max_iterations, center, initialscale * pow((finalscale/initialscale), ((double) i)/(framecount - 1)), resolution, output[i]);
    }
}

/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
	//Tips on how to get started on main function: 
	//MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
	//Mayke you complete the steps below in order. 

	//STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
	/*
	Check the spec for examples of invalid inputs.
	Remember to use your solution to B.1.1 to process colorfile.
	*/
	if(argc != 11) {
		return 1;
	}
	double threshold = atof(argv[1]);
	u_int64_t max_iterations = atol(argv[2]);
	double center_real = atof(argv[3]);
	double center_imaginary = atof(argv[4]);
	double initialscale = atof(argv[5]);
	double finalscale = atof(argv[6]);
	int framecount = atoi(argv[7]);
	u_int64_t resolution= atol(argv[8]);
	int pixel = resolution * 2 + 1;
	if(threshold <= 0 || max_iterations <= 0 || initialscale <= 0 || finalscale <= 0) {
		return 1;
	}
	if(framecount > 10000 || framecount <= 0) {
		return 1;
	}
	if(framecount == 1 && initialscale != finalscale) {
		return 1;
	}
	if(resolution < 0) {
		return 1;
	}
	int colorcount;
	u_int8_t** colormap = FileToColorMap(argv[10], &colorcount);
	if(colormap == NULL) {
		return 1;
	}
	u_int64_t** output = (u_int64_t**) malloc(sizeof(u_int64_t*) * framecount);
	if(output == NULL) {
		return 1;
	}
	for(int i =0; i<framecount; i++) {
		output[i] = (u_int64_t*) malloc(sizeof(u_int64_t) * (pixel * pixel));
		if(output[i] == NULL) {
			for(int j = 0; j < i; j++) {
				free(output[j]);
			}
			free(output);
			return 1;
		}
	}
	//STEP 2: Run MandelMovie on the correct arguments.
	/*
	MandelMovie requires an output array, so make sure you allocate the proper amount of space. 
	If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
	*/
	ComplexNumber* center = newComplexNumber(center_real, center_imaginary);
	MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, output);

	//STEP 3: Output the results of MandelMovie to .ppm files.
	/*
	Convert from iteration count to colors, and output the results into output files.
	Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
	Feel free to create your own helper function to complete this step.
	As a reminder, we are using P6 format, not P3.
	*/
	char* output_folder = argv[9];
	for(int p = 0; p < framecount; p++) {
		char frame_num[120];
		sprintf(frame_num, "%s/frame%05d.ppm", output_folder, p);
		FILE* result = fopen(frame_num, "w+");
		fprintf(result, "P6 %u %u 255\n", pixel, pixel);
		u_int64_t* curr = output[p];
		int index = 0;
		for(int o = 0; o < pixel * pixel; o++) {
			if(curr[o] == 0) {
				//int arr[3] = {0, 0, 0};
				//fwrite(arr,1, 3, result);
				fprintf(result, "%c%c%c", 0, 0, 0);
				index++;
			}
			else{
				int temp = (curr[o] - 1) % colorcount;
				fwrite(colormap[temp], 1, 3, result);
				index++;
			}
		}
		fclose(result);
	}

	//STEP 4: Free all allocated memory
	/*
	Make sure there's no memory leak.
	*/
	freeComplexNumber(center);
	for(int k = 0; k < colorcount; k++) {
		free(colormap[k]);
	}
	free(colormap);
	for(int r = 0; r < framecount; r++) {
		free(output[r]);
	}
	free(output);
	return 0;
}

