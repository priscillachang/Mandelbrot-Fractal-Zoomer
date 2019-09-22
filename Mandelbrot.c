/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
	ComplexNumber* Z = newComplexNumber(0, 0);
	ComplexNumber* Z_sqr;
	ComplexNumber* M;
    for (int iter = 0; iter < maxiters; iter++) {
    	Z_sqr = ComplexProduct(Z, Z);
    	M = ComplexSum(Z_sqr, point);
    	if(ComplexAbs(M) >= threshold) {
    		freeComplexNumber(Z);
    		freeComplexNumber(Z_sqr);
    		freeComplexNumber(M);
    		return iter + 1;
    	}
    	freeComplexNumber(Z);
        freeComplexNumber(Z_sqr);
    	Z = M;
    }
    freeComplexNumber(Z);
  return 0;
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    double real_left = Re(center) - scale;
    double im_left = Im(center) + scale;
    //ComplexNumber* new = newComplexNumber(real_left, im_left);
    ComplexNumber* ref;
    int pixel = resolution * 2 + 1;
    int index = 0;
    for(int i = 0; i < pixel; i++) {
        for(int j = 0; j < pixel; j++) {
            ref = newComplexNumber(real_left + (j * (scale/resolution)), im_left - (i * (scale/resolution)));
            output[index] = MandelbrotIterations(max_iterations, ref, threshold);
            index++;
            //ref = newComplexNumber((Re(new) + (scale/resolution)), Im(new));
            free(ref);
        }
    }
}


