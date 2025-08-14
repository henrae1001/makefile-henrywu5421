# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2
CFLAGS_DEBUG := -Wall -Wextra -std=c99 -g -DDEBUG
LDFLAGS := -L./nn/lib -lnn -lm

# Directories
NN_DIR := nn
SRC_FILES := main.c
TARGET := neural_network
TARGET_DEBUG := neural_network_debug

# Library paths
NN_INCLUDE := -I$(NN_DIR)/include
NN_STATIC_LIB := $(NN_DIR)/lib/libnn.a
NN_DYNAMIC_LIB := $(NN_DIR)/lib/libnn.so

# Default target
.PHONY: all debug run clean help
.DEFAULT_GOAL := all

# Build the project with optimizations (using dynamic library)
all: $(NN_DYNAMIC_LIB) $(TARGET)
	@echo "Build completed successfully"

# Build the project with debug information
debug: $(NN_STATIC_LIB) $(TARGET_DEBUG)
	@echo "Debug build completed successfully"

# Build the main executable (optimized)
$(TARGET): $(SRC_FILES) $(NN_DYNAMIC_LIB)
	@echo "Linking $(TARGET) with dynamic library"
	@$(CC) $(CFLAGS) $(NN_INCLUDE) -o $@ $(SRC_FILES) $(LDFLAGS)

# Build the debug executable
$(TARGET_DEBUG): $(SRC_FILES) $(NN_STATIC_LIB)
	@echo "Linking $(TARGET_DEBUG) with static library"
	@$(CC) $(CFLAGS_DEBUG) $(NN_INCLUDE) -o $@ $(SRC_FILES) $(NN_STATIC_LIB) -lm

# Build neural network static library
$(NN_STATIC_LIB):
	@echo "Building neural network static library"
	@$(MAKE) -C $(NN_DIR) static

# Build neural network dynamic library
$(NN_DYNAMIC_LIB):
	@echo "Building neural network dynamic library"
	@$(MAKE) -C $(NN_DIR) dynamic

# Run the program
run: $(TARGET)
	@echo "Running neural network program"
	@LD_LIBRARY_PATH=./$(NN_DIR)/lib:$$LD_LIBRARY_PATH ./$(TARGET)

# Remove all object files, libraries, and executables
clean:
	@echo "Cleaning neural network project"
	@$(MAKE) -C $(NN_DIR) clean
	@rm -f $(TARGET) $(TARGET_DEBUG)
	@echo "Clean completed"

# Show this help message
help:
	@echo "Neural Network Project Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all     - Build the project with optimizations (using dynamic library)"
	@echo "  debug   - Build the project with debug information"
	@echo "  run     - Run the program"
	@echo "  clean   - Remove all object files, libraries, and executables"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Variables you can override:"
	@echo "  CC      - Compiler (default: $(CC))"
	@echo "  CFLAGS  - Compiler flags for optimized build (default: $(CFLAGS))"