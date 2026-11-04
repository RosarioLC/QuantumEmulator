#pragma once


typedef struct {
    double real;
    double imaginary;
} Complex;

Complex complex_add(Complex a, Complex b);
Complex complex_mult(Complex a, Complex b);
Complex complex_conjugate(Complex a);
double complex_mag_squared(Complex a);