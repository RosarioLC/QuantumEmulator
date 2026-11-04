# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Source files
SRC_FILES = $(SRC_DIR)/complex.c \
            $(SRC_DIR)/quantum_state.c \
            $(SRC_DIR)/matrix.c \
            $(SRC_DIR)/gates.c

# Object files
OBJ_FILES = $(SRC_FILES:.c=.o)

# Executables
MAIN = main

# Default target
all: $(MAIN)

# Build main
$(MAIN): main.c $(OBJ_FILES)
	$(CC) $(CFLAGS) main.c $(OBJ_FILES) -o $(MAIN) $(LDFLAGS)

# Compile source files to object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run main
run: $(MAIN)
	./$(MAIN)

# Debug build
debug: CFLAGS += -g -O0
debug: clean all

# Clean build artifacts
clean:
	rm -f $(OBJ_FILES) $(MAIN)
	rm -f *.o $(SRC_DIR)/*.o

# Clean and rebuild
rebuild: clean all

# Help
help:
	@echo "Quantum Emulator Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  make          - Build the main executable"
	@echo "  make run      - Build and run main"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make clean    - Remove all build artifacts"
	@echo "  make rebuild  - Clean and rebuild everything"
	@echo "  make help     - Show this help message"

.PHONY: all run debug clean rebuild help