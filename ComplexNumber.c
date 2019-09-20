/*********************
**  Complex Numbers
**  This file contains a few functions that will be useful when performing computations with complex numbers
**  It is advised that you work on this part first.
**********************/

#include "ComplexNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct ComplexNumber
{
	double real;
	double imaginary;
}ComplexNumber;

//Returns a pointer to a new Complex Number with the given real and imaginary components
ComplexNumber* newComplexNumber(double real_component, double imaginary_component)
{
    struct ComplexNumber* new = (struct ComplexNumber*) malloc(sizeof(ComplexNumber));
	new -> real = real_component;
	new -> imaginary = imaginary_component;
	return new;
}

//Returns a pointer to a new Complex Number equal to a*b
ComplexNumber* ComplexProduct(ComplexNumber* a, ComplexNumber* b)
{
	double a_real = Re(a);
	double b_real = Re(b);
	double a_imag = Im(a);
	double b_imag = Im(b);
    double real_component = (a_real * b_real) - (a_imag * b_imag);
    double imaginary_component = (a_real * b_imag) + (b_real * a_imag);
	return newComplexNumber(real_component, imaginary_component);
}

//Returns a pointer to a new Complex Number equal to a+b
ComplexNumber* ComplexSum(ComplexNumber* a, ComplexNumber* b)
{
    double a_real = Re(a);
	double b_real = Re(b);
	double a_imag = Im(a);
	double b_imag = Im(b);
	double real_component = (a_real + b_real);
    double imaginary_component = (a_imag + b_imag);
	return newComplexNumber(real_component, imaginary_component);
}

//Returns the absolute value of Complex Number a
double ComplexAbs(ComplexNumber* a)
{
    double a_real = Re(a);
    double a_imag = Im(a);
    double mag = (a_real * a_real) + (a_imag * a_imag);
	return sqrt(mag);
}

void freeComplexNumber(ComplexNumber* a)
{
	free(a);
}

double Re(ComplexNumber* a)
{
	return a->real;
}
double Im(ComplexNumber* a)
{
	return a->imaginary;
}


//Contains a few tests.
int test_complex_number()
{
	ComplexNumber* a = newComplexNumber(2.0, 1.0);
	if (a == NULL)
	{
		printf("Creation of complex numbers not implemented\n");
		return 0;
	}
	ComplexNumber* b = ComplexProduct(a, a);
	if (b == NULL)
	{
		printf("Multiplication of complex numbers not implemented\n");
		free(a);
		return 0;
	}
	ComplexNumber* c = ComplexSum(b, b);
	if (c == NULL)
	{
		printf("Addition of complex numbers not implemented\n");
		free(a);
		free(b);
		return 0;
	}
	float d = ComplexAbs(c);
	if (d == 0)
	{
		printf("Absolute Value of complex numbers not implemented\n");
		free(a);
		free(b);
		free(c);
		return 0;
	}
	else if (fabsf(d - 10) < 0.0001)
	{
		printf("Sample tests for complex numbers all passed\n");
	}
	else
	{
		printf("At least one of your functions is incorrect\n");
	}
	free(a);
	free(b);
	free(c);
	return 0;
}
