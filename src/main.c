#include "./include/quantum_state.h"


int main(void) {
    QuantumState* state = quantum_state_create(3);
    quantum_state_init(state);
    quantum_state_print(state);
    QuantumState* clone = quantum_state_clone(state);
    quantum_state_destroy(state);
    quantum_state_print(clone);
    return 0;
}