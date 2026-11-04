#include "./include/quantum_state.h"
#include "./include/gates.h"

#include <stdio.h>

int main(void) {
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║     Quantum Computer Emulator - Phase 2 Demo            ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n\n");
    
    // Demo 1: Simple superposition
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Demo 1: Hadamard creates superposition\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    QuantumState* state1 = quantum_state_create(2);
    quantum_state_init(state1);
    printf("Initial state:\n");
    quantum_state_print(state1);
    
    gate_h(state1, 0);
    printf("\nAfter H on q0:\n");
    quantum_state_print(state1);
    printf("Norm: %.10d\n\n", quantum_state_norm(state1));
    quantum_state_destroy(state1);
    
    // Demo 2: Bell state
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Demo 2: Creating a Bell state (entanglement)\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    QuantumState* state2 = quantum_state_create(2);
    quantum_state_init(state2);
    printf("Initial state:\n");
    quantum_state_print(state2);
    
    gate_h(state2, 0);
    printf("\nAfter H on q0:\n");
    quantum_state_print(state2);
    
    gate_cx(state2, 0, 1);
    printf("\nAfter CX(q0->q1) — Bell state:\n");
    quantum_state_print(state2);
    printf("Norm: %.10d\n\n", quantum_state_norm(state2));
    quantum_state_destroy(state2);
    
    // Demo 3: Phase gates
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Demo 3: Phase gates create imaginary amplitudes\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    QuantumState* state3 = quantum_state_create(1);
    quantum_state_init(state3);
    
    gate_h(state3, 0);
    printf("After H:\n");
    quantum_state_print(state3);
    
    gate_s(state3, 0);
    printf("\nAfter S gate (phase shift):\n");
    quantum_state_print(state3);
    printf("Norm: %.10d\n\n", quantum_state_norm(state3));
    quantum_state_destroy(state3);
    
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                    Demo Complete!                        ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    
    return 0;
}