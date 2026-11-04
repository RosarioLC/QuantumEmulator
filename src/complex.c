#include "../include/complex.h"

Complex complex_add(Complex a, Complex b) {
    return (Complex) {a.real + b.real, a.imaginary + b.imaginary};
}


Complex complex_mult(Complex a, Complex b) {
    return (Complex) {(a.real * b.real) - (a.imaginary * b.imaginary), (a.real * b.imaginary) + (a.imaginary * b.real)};
}

Complex complex_conjugate(Complex a) {
    return (Complex) {a.real, - a.imaginary};
}


double complex_mag_squared(Complex a) {
    return a.real * a.real + a.imaginary * a.imaginary;
}