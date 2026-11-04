# Quantum Computer Emulator in Pure C

A from-scratch quantum state-vector simulator written entirely in C using only the standard library. No external dependencies, no quantum computing frameworks—just pure C and quantum mechanics.

## 🎯 Project Goals

- Build a fully functional quantum computer emulator without any external libraries
- Understand quantum computing at the lowest level by implementing everything from scratch
- Create a portable, educational tool that demonstrates quantum state evolution and measurement

## 🚧 Current Status

**Phase 1: Memory and State Management** ✅ *Complete*
- Custom complex number implementation (no `<complex.h>`)
- Quantum state allocation, initialization, and cleanup
- State cloning and reset functionality
- Norm calculation and normalization
- State vector visualization with binary basis representation

**Phase 2: Gate Application Engine** 🔲 *In Progress*
- Optimized bitwise gate application (no matrix multiplication)
- Single-qubit gates (H, X, Y, Z, S, T, Rx, Ry, Rz)
- Two-qubit gates (CNOT, CZ, SWAP)
- Three-qubit gates (Toffoli, Fredkin)

**Phase 3: Measurement and Collapse** 🔲 *Planned*
- Single-qubit measurement with state collapse
- Full-state measurement
- Probability calculation
- Custom PRNG implementation

**Phase 4: Circuit Management** 🔲 *Planned*
- Circuit data structure
- Gate sequencing
- Multi-shot execution
- Result histogramming

## 📁 Project Structure
quantum-emulator-c/
│
├── README.md
├── LICENSE
├── Makefile
├── .gitignore
│
├── src/
│   ├── main.c                ← entry point
│   ├── complex.c             ← complex number implementation
│   ├── quantum_state.c       ← state management
│   ├── gates.c               ← (Phase 2) gate application engine
│   ├── measurement.c         ← (Phase 3) measurement & collapse
│   └── circuit.c             ← (Phase 4) circuit management
│
├── include/
│   ├── complex.h
│   ├── quantum_state.h
│   ├── gates.h               ← (Phase 2)
│   ├── measurement.h         ← (Phase 3)
│   └── circuit.h             ← (Phase 4)
│
└── tests/
    ├── test_complex.c        ← unit tests for complex math
    ├── test_state.c          ← unit tests for state management
    └── run_tests.sh          ← (optional) test runner script


## 🔧 Building

### Requirements

- GCC or Clang compiler
- Standard C library (C99 or newer)
- `make` (optional, but recommended)

### Using Make (Recommended)

```bash
# Build the project
make

# Run the emulator
./main

# Build with debug symbols
make debug

# Clean build artifacts
make clean