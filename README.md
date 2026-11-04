# ⚛️ Quantum Computer Emulator in Pure C

A from-scratch **quantum state-vector simulator** written entirely in C, using only the standard library.

No external dependencies. No quantum computing frameworks. Just pure C, bitwise operations, complex numbers, and quantum mechanics.

---

## 🎯 Project Goals

- Build a fully functional quantum computer emulator without external libraries.
- Understand quantum computing fundamentals by implementing everything from scratch.
- Create a portable and educational tool to demonstrate quantum state evolution, quantum gates, and measurement.
- Explore efficient quantum gate simulation using bitwise operations instead of matrix multiplication.

---

## 🚧 Project Status

The project is being developed in several phases:

### Phase 1 — Memory and State Management

<sup>✅ Complete</sup>

- [x] Custom complex number implementation (without `<complex.h>`).
- [x] Quantum state allocation, initialization, and cleanup.
- [x] State cloning and reset functionality.
- [x] Norm calculation and state normalization.
- [x] State vector visualization using binary basis representations.

### Phase 2 — Gate Application Engine

<sup>✅ Complete</sup>

- [x] Optimized bitwise gate application (without explicit matrix multiplication).
- [x] **Single-qubit gates:** H, X, Y, Z, S, T, Rx, Ry, Rz.
- [x] **Two-qubit gates:** CNOT, CZ, SWAP.
- [x] **Three-qubit gates:** Toffoli, Fredkin.

### Phase 3 — Measurement and Collapse

<sup>📋 Planned</sup>

- [ ] Single-qubit measurement with state collapse.
- [ ] Full-state measurement.
- [ ] Probability calculation.
- [ ] Custom pseudo-random number generator (PRNG).

### Phase 4 — Circuit Management

<sup>📋 Planned</sup>

- [ ] Circuit data structure.
- [ ] Gate sequencing and execution.
- [ ] Multi-shot circuit execution.
- [ ] Measurement result histogramming.

---

## 📁 Project Structure

```text
quantum-emulator-c/
│
├── README.md
├── LICENSE
├── Makefile
├── .gitignore
│
├── src/
│   ├── main.c                # Entry point
│   ├── complex.c             # Complex number implementation
│   ├── quantum_state.c       # Quantum state management
│   ├── gates.c               # Gate application engine (Phase 2)
│   ├── measurement.c         # Measurement and collapse (Phase 3)
│   └── circuit.c             # Circuit management (Phase 4)
│
├── include/
│   ├── complex.h
│   ├── quantum_state.h
│   ├── gates.h               # Phase 2
│   ├── measurement.h         # Phase 3
│   └── circuit.h             # Phase 4
│
└── tests/
    ├── test_complex.c        # Complex number unit tests
    ├── test_state.c          # Quantum state unit tests
    └── run_tests.sh          # Test runner script (optional)
```

---

## 🔧 Building

### Requirements

- GCC or Clang
- C99-compatible compiler
- Standard C library
- GNU Make (optional, but recommended)

### Build with Make

Clone the repository:

```bash
git clone <https://github.com/RosarioLC/QuantumEmulator.git>
cd quantum-emulator-c
```

Build the project:

```bash
make
```

Run the emulator:

```bash
./main
```

### Additional Commands

Build with debug symbols:

```bash
make debug
```

Clean build artifacts:

```bash
make clean
```

---

## 🧪 Testing

Run the test suite:

```bash
./tests/run_tests.sh
```

---

## 🛠️ Technologies

- **Language:** C (C99 or newer)
- **Dependencies:** None (standard library only)
- **Compiler:** GCC / Clang
- **Build system:** GNU Make

---

## 📚 Learning Objectives

This project is also an exploration of the underlying mathematics and computational principles of quantum computing:

- Complex amplitudes and quantum state vectors.
- Superposition and entanglement.
- Unitary transformations and quantum gates.
- Probabilistic measurement and wavefunction collapse.
- Bitwise indexing and efficient state-vector manipulation.
- Quantum circuit construction and simulation.

---

## 📌 Roadmap

The ultimate goal is to support the simulation of complete quantum circuits, from individual gate operations to repeated measurements and statistical result analysis.

