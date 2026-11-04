#pragma once

#include "complex.h"

#include <stdbool.h>

typedef struct {
    int rows;
    int cols;
    Complex* data;
} ComplexMatrix;

ComplexMatrix* matrix_create(int rows, int cols);
ComplexMatrix* matrix_identity(int size);
void matrix_destroy(ComplexMatrix* matrix);

Complex matrix_get(ComplexMatrix* matrix, int i, int j);
void matrix_set(ComplexMatrix* matrix, int i, int j, Complex value);

ComplexMatrix* matrix_multiply(ComplexMatrix* a, ComplexMatrix* b);
ComplexMatrix* matrix_vetor_multiply(ComplexMatrix* a, Complex* vector, int size);

ComplexMatrix* matrix_add(ComplexMatrix* a, ComplexMatrix* b);
ComplexMatrix* matrix_sub(ComplexMatrix* a, ComplexMatrix* b);

ComplexMatrix* matrix_transpose(ComplexMatrix* a);
ComplexMatrix* matrix_adjoint(ComplexMatrix* a);

bool matrix_equals(ComplexMatrix* a, ComplexMatrix* b, double epsilon);

void matrix_print(ComplexMatrix* a);

bool matrix_is_unitary(ComplexMatrix* a);