#pragma once

#include "complex.h"

typedef struct {
    Complex* state_vector;
    int n;
    int dim;
} QuantumState;

QuantumState* quantum_state_create(int n);
void quantum_state_init(QuantumState* state);
void quantum_state_destroy(QuantumState* state);
QuantumState* quantum_state_clone(QuantumState* state);
void quantum_state_reset(QuantumState* state);
int quantum_state_calculate_norm(QuantumState* state);
void quantum_state_normalize(QuantumState* state);
void quantum_state_print(QuantumState* state);