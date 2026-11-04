#pragma once

#include "complex.h"
#include "matrix.h"
#include "quantum_state.h"

void apply_single_qubit_gate(QuantumState* state, int target, ComplexMatrix* U);

void apply_controlled_gate(QuantumState* state, int control, int target, ComplexMatrix* U);

void apply_multi_controlled_gate(QuantumState* state, const int* controls, int num_controls, int target, ComplexMatrix* U);

ComplexMatrix* create_pauli_x_matrix(void);
ComplexMatrix* create_pauli_y_matrix(void);
ComplexMatrix* create_pauli_z_matrix(void);
ComplexMatrix* create_hadamard_matrix(void);
ComplexMatrix* create_phase_s_matrix(void);
ComplexMatrix* create_phase_t_matrix(void);

ComplexMatrix* create_rx_matrix(double angle);
ComplexMatrix* create_ry_matrix(double angle);
ComplexMatrix* create_rz_matrix(double angle);

void gate_x(QuantumState* state, int target);
void gate_y(QuantumState* state, int target);
void gate_z(QuantumState* state, int target);
void gate_h(QuantumState* state, int target);
void gate_s(QuantumState* state, int target);
void gate_t(QuantumState* state, int target);

void gate_rx(QuantumState* state, int target, double angle);
void gate_ry(QuantumState* state, int target, double angle);
void gate_rz(QuantumState* state, int target, double angle);

void gate_cx(QuantumState* state, int control, int target);
void gate_cz(QuantumState* state, int control, int target);

void gate_swap(QuantumState* state, int qubit_a, int qubit_b);
void gate_ccx(QuantumState* state, int control1, int control2, int target);
void gate_cswap(QuantumState* state, int control, int target_a, int target_b);