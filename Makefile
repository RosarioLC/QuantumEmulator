CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Iinclude
LDFLAGS = -lm

SRC = src/main.c src/complex.c src/quantum_state.c
OBJ = $(SRC:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

debug: CFLAGS += -g -O0
debug: clean all

.PHONY: all clean debug