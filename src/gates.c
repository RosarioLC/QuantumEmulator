#include "../include/gates.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>



void apply_single_qubit_gate(QuantumState* state, int target, ComplexMatrix* U) {
    if (!state || !U) return;
    if (target < 0 || target >= state->n) {
        fprintf(stderr, "Error: target qubit %d out of range [0, %d)\n", target, state->n);
        return;
    }

    uint64_t step = 1ULL << target;

    Complex u00 = matrix_get(U, 0, 0);
    Complex u01 = matrix_get(U, 0, 1);
    Complex u10 = matrix_get(U, 1, 0);
    Complex u11 = matrix_get(U, 1, 1);

    for (uint64_t i = 0; i < state->dim; i += 2 * step) {
        for (uint64_t j = 0; j < step; j++) {
            uint64_t idx0 = i + j;
            uint64_t idx1 = i + j + step;

            Complex a0 = state->state_vector[idx0];
            Complex a1 = state->state_vector[idx1];

            state->state_vector[idx0] = complex_add(complex_multiply(u00, a0), complex_multiply(u01, a1));
            state->state_vector[idx1] = complex_add(complex_multiply(u10, a0), complex_multiply(u11, a1));
        }
    }
}


void apply_controlled_gate(QuantumState* state, int control, int target, ComplexMatrix* U) {
    if (!state || !U) return;
    if (control < 0 || control >= state->n ||
        target < 0 || target >= state->n) {
        fprintf(stderr, "Error: qubit index out of range\n");
        return;
    }
    
    if (control == target) {
        fprintf(stderr, "Error: control and target cannot be the same qubit\n");
        return;
    }

    uint64_t step = 1ULL << target;

    Complex u00 = matrix_get(U, 0, 0);
    Complex u01 = matrix_get(U, 0, 1);
    Complex u10 = matrix_get(U, 1, 0);
    Complex u11 = matrix_get(U, 1, 1);

    for (uint64_t i = 0; i < state->dim; i += 2 * step) {
        for (uint64_t j = 0; j < step; j++) {
            uint64_t idx0 = i + j;
            uint64_t idx1 = i + j + step;

            int control_bit = (idx0 >> control) & 1;

            if (control_bit == 1) {
                Complex a0 = state->state_vector[idx0];
                Complex a1 = state->state_vector[idx1];

                state->state_vector[idx0] = complex_add(complex_multiply(u00, a0), complex_multiply(u01, a1));
                state->state_vector[idx1] = complex_add(complex_multiply(u10, a0), complex_multiply(u11, a1));
            }
        }
    }
}


void apply_multi_controlled_gate(QuantumState* state, const int* controls, int num_controls, int target, ComplexMatrix* U) {
    if (!state || !U || !controls) return;
    if (target < 0 || target >= state->n) return;
    for (int k = 0; k < num_controls; k++) {
        if (controls[k] < 0 || controls[k] >= state->n || controls[k] == target) {
            fprintf(stderr, "Error: invalid control qubit\n");
            return;
        }
    }

    uint64_t control_mask = 0;
    for (int k = 0; k < num_controls; k++) {
        control_mask |= (1ULL << controls[k]);
    }

    Complex u00 = matrix_get(U, 0, 0);
    Complex u01 = matrix_get(U, 0, 1);
    Complex u10 = matrix_get(U, 1, 0);
    Complex u11 = matrix_get(U, 1, 1);

    for (uint64_t i = 0; i < state->dim; i++) {
        if ((i & control_mask) == control_mask) {
            uint64_t partner = i ^ (1ULL << target);

            if (((i >> target) & 1) == 0) {
                Complex a0 = state->state_vector[i];
                Complex a1 = state->state_vector[partner];

                state->state_vector[i]       = complex_add(complex_multiply(u00, a0), complex_multiply(u01, a1));
                state->state_vector[partner] = complex_add(complex_multiply(u10, a0), complex_multiply(u11, a1));
            }
        }
    }
}


ComplexMatrix* create_pauli_x_matrix(void) {
    ComplexMatrix* m = matrix_create(2, 2);
    matrix_set(m, 0, 0, (Complex){0.0, 0.0});
    matrix_set(m, 0, 1, (Complex){1.0, 0.0});
    matrix_set(m, 1, 0, (Complex){1.0, 0.0});
    matrix_set(m, 1, 1, (Complex){0.0, 0.0});
    return m;
}


ComplexMatrix* create_pauli_y_matrix(void) {
    ComplexMatrix* m = matrix_create(2, 2);
    matrix_set(m, 0, 0, (Complex){0.0,  0.0});
    matrix_set(m, 0, 1, (Complex){0.0, -1.0});
    matrix_set(m, 1, 0, (Complex){0.0,  1.0});
    matrix_set(m, 1, 1, (Complex){0.0,  0.0});
    return m;
}


ComplexMatrix* create_pauli_z_matrix(void) {
    ComplexMatrix* m = matrix_create(2, 2);
    matrix_set(m, 0, 0, (Complex){ 1.0, 0.0});
    matrix_set(m, 0, 1, (Complex){ 0.0, 0.0});
    matrix_set(m, 1, 0, (Complex){ 0.0, 0.0});
    matrix_set(m, 1, 1, (Complex){-1.0, 0.0});
    return m;
}


ComplexMatrix* create_hadamard_matrix(void) {
    ComplexMatrix* m = matrix_create(2, 2);
    double inv = 1.0 / sqrt(2.0);
    matrix_set(m, 0, 0, (Complex){ inv, 0.0});
    matrix_set(m, 0, 1, (Complex){ inv, 0.0});
    matrix_set(m, 1, 0, (Complex){ inv, 0.0});
    matrix_set(m, 1, 1, (Complex){-inv, 0.0});
    return m;
}


ComplexMatrix* create_phase_s_matrix(void) {
    ComplexMatrix* m = matrix_create(2, 2);
    matrix_set(m, 0, 0, (Complex){1.0, 0.0});
    matrix_set(m, 0, 1, (Complex){0.0, 0.0});
    matrix_set(m, 1, 0, (Complex){0.0, 0.0});
    matrix_set(m, 1, 1, (Complex){0.0, 1.0}); 
    return m;
}


ComplexMatrix* create_phase_t_matrix(void) {
    ComplexMatrix* m = matrix_create(2, 2);
    double inv = 1.0 / sqrt(2.0);
    matrix_set(m, 0, 0, (Complex){1.0, 0.0});
    matrix_set(m, 0, 1, (Complex){0.0, 0.0});
    matrix_set(m, 1, 0, (Complex){0.0, 0.0});
    matrix_set(m, 1, 1, (Complex){inv, inv});
    return m;
}


ComplexMatrix* create_rx_matrix(double angle) {
    ComplexMatrix* m = matrix_create(2, 2);
    double c = cos(angle / 2.0);
    double s = sin(angle / 2.0);
    matrix_set(m, 0, 0, (Complex){ c,  0.0});
    matrix_set(m, 0, 1, (Complex){0.0,  -s});
    matrix_set(m, 1, 0, (Complex){0.0,  -s});
    matrix_set(m, 1, 1, (Complex){ c,  0.0});
    return m;
}


ComplexMatrix* create_ry_matrix(double angle) {
    ComplexMatrix* m = matrix_create(2, 2);
    double c = cos(angle / 2.0);
    double s = sin(angle / 2.0);
    matrix_set(m, 0, 0, (Complex){ c, 0.0});
    matrix_set(m, 0, 1, (Complex){-s, 0.0});
    matrix_set(m, 1, 0, (Complex){ s, 0.0});
    matrix_set(m, 1, 1, (Complex){ c, 0.0});
    return m;
}


ComplexMatrix* create_rz_matrix(double angle) {
    ComplexMatrix* m = matrix_create(2, 2);
    matrix_set(m, 0, 0, (Complex){cos(-angle / 2.0), sin(-angle / 2.0)});
    matrix_set(m, 0, 1, (Complex){0.0, 0.0});
    matrix_set(m, 1, 0, (Complex){0.0, 0.0});
    matrix_set(m, 1, 1, (Complex){cos( angle / 2.0), sin( angle / 2.0)});
    return m;
}


void gate_x(QuantumState* state, int target) {
    ComplexMatrix* u = create_pauli_x_matrix();
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_y(QuantumState* state, int target) {
    ComplexMatrix* u = create_pauli_y_matrix();
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_z(QuantumState* state, int target) {
    ComplexMatrix* u = create_pauli_z_matrix();
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_h(QuantumState* state, int target) {
    ComplexMatrix* u = create_hadamard_matrix();
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_s(QuantumState* state, int target) {
    ComplexMatrix* u = create_phase_s_matrix();
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_t(QuantumState* state, int target) {
    ComplexMatrix* u = create_phase_t_matrix();
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_rx(QuantumState* state, int target, double angle) {
    ComplexMatrix* u = create_rx_matrix(angle);
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_ry(QuantumState* state, int target, double angle) {
    ComplexMatrix* u = create_ry_matrix(angle);
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_rz(QuantumState* state, int target, double angle) {
    ComplexMatrix* u = create_rz_matrix(angle);
    apply_single_qubit_gate(state, target, u);
    matrix_destroy(u);
}


void gate_cx(QuantumState* state, int control, int target) {
    ComplexMatrix* u = create_pauli_x_matrix();
    apply_controlled_gate(state, control, target, u);
    matrix_destroy(u);
}


void gate_cz(QuantumState* state, int control, int target) {
    ComplexMatrix* u = create_pauli_z_matrix();
    apply_controlled_gate(state, control, target, u);
    matrix_destroy(u);
}


void gate_swap(QuantumState* state, int qubit_a, int qubit_b) {
    gate_cx(state, qubit_a, qubit_b);
    gate_cx(state, qubit_b, qubit_a);
    gate_cx(state, qubit_a, qubit_b);
}

void gate_ccx(QuantumState* state, int control1, int control2, int target) {
    int controls[2] = {control1, control2};
    ComplexMatrix* u = create_pauli_x_matrix();
    apply_multi_controlled_gate(state, controls, 2, target, u);
    matrix_destroy(u);
}


void gate_cswap(QuantumState* state, int control, int target_a, int target_b) {
    gate_cx(state, target_b, target_a);
    gate_ccx(state, control, target_a, target_b);
    gate_cx(state, target_b, target_a);
}