#include "quantum_state.h"
#include "complex.h"

#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

char* int_to_binary(unsigned int n) {
    int total_bits = sizeof(n) * 8;
    
    char* buffer = (char*)malloc(total_bits + 1);
    if (buffer == NULL) return NULL; 

    buffer[total_bits] = '\0';
    int first_one_index = -1;

    for (int i = total_bits - 1; i >= 0; i--) {
        if (n & 1) {
            buffer[i] = '1';
            first_one_index = i;
        } else {
            buffer[i] = '0';
        }
        n >>= 1;
    }

    if (first_one_index == -1) {
        char* zero_str = (char*)malloc(2);
        if (zero_str == NULL) { free(buffer); return NULL; }
        zero_str[0] = '0';
        zero_str[1] = '\0';
        free(buffer);
        return zero_str;
    }

    int clean_len = total_bits - first_one_index;
    
    char* clean_str = (char*)malloc(clean_len + 1);
    if (clean_str == NULL) { free(buffer); return NULL; }

    for (int i = 0; i < clean_len; i++) {
        clean_str[i] = buffer[first_one_index + i];
    }
    clean_str[clean_len] = '\0';

    free(buffer); 
    
    return clean_str;
}


QuantumState* quantum_state_create(int n) {
    int dim = pow(2, n);
    Complex* vec = (Complex*)malloc(sizeof(Complex) * dim);
    if (!vec) return NULL;

    QuantumState* state = (QuantumState*)malloc(sizeof(QuantumState));
    if (!state) return NULL;
    
    state->state_vector = vec;
    state->n = n;
    state->dim = dim;

    return state;
}


void quantum_state_init(QuantumState* state) {
    if (!state) return;

    state->state_vector[0] = (Complex) {1, 0};

    for (int i = 1; i < state->dim; i++) {
        state->state_vector[i] = (Complex) {0, 0};
    }
}


void quantum_state_destroy(QuantumState* state) {
    if (!state) return;

    free(state->state_vector);
    state->state_vector = NULL;
}

QuantumState* quantum_state_clone(QuantumState* state) {
    if (!state) return NULL;

    QuantumState* ret = (QuantumState*)malloc(sizeof(QuantumState));
    if (!ret) return NULL;

    ret->dim = state->dim;
    ret->n = state->n;

    Complex* vec = (Complex*)malloc(sizeof(Complex) * ret->dim);
    if (!vec) return NULL;

    ret->state_vector = vec;

    for (int i = 0; i < ret->dim; i++) {
        Complex c = state->state_vector[i];
        ret->state_vector[i] = (Complex) {c.real, c.imaginary};
    }

    return ret;
}   


void quantum_state_reset(QuantumState* state) {
    if (!state) return;

    state->state_vector[0] = (Complex) {1, 0};

    for (int i = 1; i < state->dim; i++) {
        state->state_vector[i] = (Complex) {0, 0};
    }
}


int quantum_state_norm(QuantumState* state) {
    if (!state) return -1;

    int sum = 0;

    for (int i = 0; i < state->dim; i++) {
        sum += complex_mag_squared(state->state_vector[i]);
    }

    return sum;
}


void quantum_state_normalize(QuantumState* state) {
    if (!state) return;

    int sqrt_norm = sqrt(quantum_state_norm(state));

    for (int i = 0; i < state->dim; i++) {
        Complex c = state->state_vector[i];
        state->state_vector[i] = (Complex) {c.real / sqrt_norm, c.imaginary / sqrt_norm};
    }
}

void quantum_state_print(QuantumState* state) {
    if (!state) return;

    for (int i = 0; i < state->dim; i++) {
        char* index = int_to_binary(i);
        Complex c = state->state_vector[i];
        double mag = complex_mag_squared(c);

        printf("idx %d, |%s>\treal:%f\timag:%f\tprob:%f\tpct:%f%%\n", i, index, c.real, c.imaginary, mag, (double)(mag*100));
        free(index);
    }

    printf("norm: %d\n", quantum_state_norm(state));
}