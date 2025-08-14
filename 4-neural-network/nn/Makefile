# nn Makefile

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2
# fPIC 讓程式碼可以在記憶體的任何位置執行，動態函式庫需要這個特性
CFLAGS_PIC := $(CFLAGS) -fPIC
CFLAGS_DEBUG := -Wall -Wextra -std=c99 -g -DDEBUG

# Directories
SRC_DIR := src/nn
INCLUDE_DIR := include
LIB_DIR := lib
OBJ_DIR := obj

# Source files and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJECTS_PIC := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.pic.o)

# Library names
STATIC_LIB := $(LIB_DIR)/libnn.a
DYNAMIC_LIB := $(LIB_DIR)/libnn.so

# Installation directories
INSTALL_LIB_DIR := /usr/local/lib
INSTALL_INCLUDE_DIR := /usr/local/include

# Default target
.PHONY: all static dynamic clean help install uninstall debug
.DEFAULT_GOAL := all

all: static dynamic

# Create necessary directories
$(OBJ_DIR) $(LIB_DIR):
	@mkdir -p $@

# Compile object files for static library
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $< (static)"
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile object files for dynamic library (with -fPIC)
$(OBJ_DIR)/%.pic.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $< (dynamic)"
	@$(CC) $(CFLAGS_PIC) -I$(INCLUDE_DIR) -c $< -o $@

# Build static library
static: $(STATIC_LIB)
$(STATIC_LIB): $(OBJECTS) | $(LIB_DIR)
	@echo "Creating static library $@"
	@ar rcs $@ $^
	@echo "Static library created successfully"

# Build dynamic library
dynamic: $(DYNAMIC_LIB)
$(DYNAMIC_LIB): $(OBJECTS_PIC) | $(LIB_DIR)
	@echo "Creating dynamic library $@"
	@$(CC) -shared -o $@ $^
	@echo "Dynamic library created successfully"

# Debug build
debug: CFLAGS := $(CFLAGS_DEBUG)
debug: CFLAGS_PIC := $(CFLAGS_DEBUG) -fPIC
debug: clean all
	@echo "Debug libraries built successfully"

# Install dynamic library and headers
install: dynamic
	@echo "Installing neural network library..."
	@sudo cp $(DYNAMIC_LIB) $(INSTALL_LIB_DIR)/
	@sudo cp -r $(INCLUDE_DIR)/nn $(INSTALL_INCLUDE_DIR)/
	@sudo ldconfig
	@echo "Installation completed"

# Uninstall library and headers
uninstall:
	@echo "Uninstalling neural network library..."
	@sudo rm -f $(INSTALL_LIB_DIR)/libnn.so
	@sudo rm -rf $(INSTALL_INCLUDE_DIR)/nn
	@sudo ldconfig
	@echo "Uninstallation completed"

# Clean build artifacts
clean:
	@echo "Cleaning neural network library..."
	@rm -rf $(OBJ_DIR) $(LIB_DIR)
	@echo "Clean completed"

# Show library information
info:
	@echo "Neural Network Library Information:"
	@echo "  Source files: $(SOURCES)"
	@echo "  Static library: $(STATIC_LIB)"
	@echo "  Dynamic library: $(DYNAMIC_LIB)"
	@echo "  Compiler: $(CC)"
	@echo "  Flags: $(CFLAGS)"
	@if [ -f $(STATIC_LIB) ]; then \
		echo "  Static library size: $$(du -h $(STATIC_LIB) | cut -f1)"; \
	fi
	@if [ -f $(DYNAMIC_LIB) ]; then \
		echo "  Dynamic library size: $$(du -h $(DYNAMIC_LIB) | cut -f1)"; \
	fi

# Check library symbols
check: $(STATIC_LIB) $(DYNAMIC_LIB)
	@echo "Static library symbols:"
	@nm -g $(STATIC_LIB) | grep -E '^[0-9a-f]+ [TDBS] ' || echo "  No symbols found"
	@echo "Dynamic library symbols:"
	@nm -gD $(DYNAMIC_LIB) | grep -E '^[0-9a-f]+ [TDBS] ' || echo "  No symbols found"

# Help target
help:
	@echo "nn/Makefile"
	@echo "Available targets:"
	@echo "  all      - Build both static and dynamic libraries (default)"
	@echo "  static   - Build static library (libnn.a)"
	@echo "  dynamic  - Build dynamic library (libnn.so)"
	@echo "  debug    - Build libraries with debug information"
	@echo "  install  - Install dynamic library to $(INSTALL_LIB_DIR)"
	@echo "  uninstall- Uninstall library from system"
	@echo "  clean    - Remove all build artifacts"
	@echo "  info     - Show library information"
	@echo "  check    - Check library symbols"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Variables you can override:"
	@echo "  CC       - Compiler (default: $(CC))"
	@echo "  CFLAGS   - Compiler flags (default: $(CFLAGS))"