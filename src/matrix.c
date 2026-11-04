#include "../include/matrix.h"

#include "../include/complex.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAT_IDX(mat, r, c) ((r) * (mat)->cols + (c))


ComplexMatrix* matrix_create(int rows, int cols) {
    ComplexMatrix* matrix = (ComplexMatrix*)malloc(sizeof(ComplexMatrix));
    if (!matrix) return NULL;

    matrix->rows = rows;
    matrix->cols = cols;

    Complex* data = (Complex*)malloc(rows * cols * sizeof(Complex));
    if (!data) {
        free(matrix);
        return NULL;
    }

    matrix->data = data;
    return matrix;
}


ComplexMatrix* matrix_identity(int size) {
    ComplexMatrix* matrix = matrix_create(size, size);
    if (!matrix) return NULL;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int index = MAT_IDX(matrix, row, col);
            if (row == col) {
                matrix->data[index] = (Complex){1.0, 0.0};
            } else {
                matrix->data[index] = (Complex){0.0, 0.0};
            }
        }
    }

    return matrix;
}


void matrix_destroy(ComplexMatrix* matrix) {
    if (!matrix) return;
    if (matrix->data) {
        free(matrix->data);
        matrix->data = NULL;
    }
    free(matrix);
}


Complex matrix_get(ComplexMatrix* matrix, int i, int j) {
    if (!matrix) return (Complex){0.0, 0.0};

    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        return matrix->data[MAT_IDX(matrix, i, j)];
    }
    return (Complex){0.0, 0.0};
}


void matrix_set(ComplexMatrix* matrix, int i, int j, Complex value) {
    if (!matrix) return;
    if (i >= 0 && i < matrix->rows && j >= 0 && j < matrix->cols) {
        matrix->data[MAT_IDX(matrix, i, j)] = value;
    }
}


ComplexMatrix* matrix_multiply(ComplexMatrix* a, ComplexMatrix* b) {
    if (!a || !b) return NULL;
    
    if (a->cols != b->rows) {
        fprintf(stderr, "Error: Cannot multiply %dx%d matrix by %dx%d matrix\n", 
                a->rows, a->cols, b->rows, b->cols);
        return NULL;
    }
    
    ComplexMatrix* c = matrix_create(a->rows, b->cols);
    if (!c) return NULL;
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            Complex sum = {0.0, 0.0};
            for (int k = 0; k < a->cols; k++) {
                Complex prod = complex_multiply(a->data[MAT_IDX(a, i, k)], b->data[MAT_IDX(b, k, j)]);
                sum = complex_add(sum, prod);
            }
            c->data[MAT_IDX(c, i, j)] = sum;
        }
    }
    
    return c;
}


Complex* matrix_vector_multiply(ComplexMatrix* matrix, Complex* vector, int vec_size) {
    if (!matrix || !vector) return NULL;
    
    if (matrix->cols != vec_size) {
        fprintf(stderr, "Error: Matrix cols (%d) must equal vector size (%d)\n", matrix->cols, vec_size);
        return NULL;
    }
    
    Complex* result = (Complex*)malloc(matrix->rows * sizeof(Complex));
    if (!result) return NULL;
    
    for (int i = 0; i < matrix->rows; i++) {
        Complex sum = {0.0, 0.0};
        for (int j = 0; j < matrix->cols; j++) {
            Complex prod = complex_multiply(matrix->data[MAT_IDX(matrix, i, j)], vector[j]);
            sum = complex_add(sum, prod);
        }
        result[i] = sum;
    }
    
    return result;
}


ComplexMatrix* matrix_add(ComplexMatrix* a, ComplexMatrix* b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) {
        fprintf(stderr, "Error: Matrices must have same dimensions to add\n");
        return NULL;
    }
    
    ComplexMatrix* c = matrix_create(a->rows, a->cols);
    if (!c) return NULL;
    
    int total = a->rows * a->cols;
    for (int i = 0; i < total; i++) {
        c->data[i] = complex_add(a->data[i], b->data[i]);
    }
    return c;
}


ComplexMatrix* matrix_sub(ComplexMatrix* a, ComplexMatrix* b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) {
        fprintf(stderr, "Error: Matrices must have same dimensions to subtract\n");
        return NULL;
    }
    
    ComplexMatrix* c = matrix_create(a->rows, a->cols);
    if (!c) return NULL;
    
    int total = a->rows * a->cols;
    for (int i = 0; i < total; i++) {
        c->data[i].real = a->data[i].real - b->data[i].real;
        c->data[i].imaginary = a->data[i].imaginary - b->data[i].imaginary;
    }
    return c;
}


ComplexMatrix* matrix_transpose(ComplexMatrix* a) {
    if (!a) return NULL;
    
    ComplexMatrix* c = matrix_create(a->cols, a->rows);
    if (!c) return NULL;
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            c->data[MAT_IDX(c, j, i)] = a->data[MAT_IDX(a, i, j)];
        }
    }
    return c;
}


ComplexMatrix* matrix_adjoint(ComplexMatrix* a) {
    if (!a) return NULL;
    
    ComplexMatrix* c = matrix_create(a->cols, a->rows);
    if (!c) return NULL;
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            c->data[MAT_IDX(c, j, i)].real = a->data[MAT_IDX(a, i, j)].real;
            c->data[MAT_IDX(c, j, i)].imaginary = -a->data[MAT_IDX(a, i, j)].imaginary;
        }
    }
    return c;
}


bool matrix_equals(ComplexMatrix* a, ComplexMatrix* b, double epsilon) {
    if (!a || !b) return false;
    if (a->rows != b->rows || a->cols != b->cols) return false;
    
    int total = a->rows * a->cols;
    for (int i = 0; i < total; i++) {
        if (fabs(a->data[i].real - b->data[i].real) > epsilon) return false;
        if (fabs(a->data[i].imaginary - b->data[i].imaginary) > epsilon) return false;
    }
    return true;
}


void matrix_print(ComplexMatrix* a) {
    if (!a) {
        printf("NULL matrix\n");
        return;
    }
    
    printf("Matrix %dx%d:\n", a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) {
        printf("[ ");
        for (int j = 0; j < a->cols; j++) {
            Complex val = a->data[MAT_IDX(a, i, j)];
            if (val.imaginary >= 0) {
                printf("%+.4f + %+.4fi ", val.real, val.imaginary);
            } else {
                printf("%+.4f - %+.4fi ", val.real, -val.imaginary);
            }
        }
        printf("]\n");
    }
}


bool matrix_is_unitary(ComplexMatrix* a) {
    if (!a) return -1;

    return matrix_equals(matrix_multiply(matrix_adjoint(a), a), matrix_identity(a->rows), 0); 
}