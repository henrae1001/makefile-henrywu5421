# Declare phony targets
.PHONY: all debug run clean help
# Set the default goal to 'all'
.DEFAULT_GOAL := all

# Project configuration
TARGET = linked_list.out
SOURCES = main.c list.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = list.h

# Compiler configuration
CC = gcc
CFLAGS_COMMON = -Wall -Wextra -Wunused-variable
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0 -DDEBUG
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2 -DNDEBUG

# Build targets
all: CFLAGS = $(CFLAGS_RELEASE)
all: $(TARGET)

debug: CFLAGS = $(CFLAGS_DEBUG)
debug: $(TARGET)_debug

# Linking rules
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(TARGET)_debug: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Implicit rule for object files (using implicit variables)
# This will use CC, CFLAGS, and CPPFLAGS automatically
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Run target and generate output
run: $(TARGET)
	@echo "Running $(TARGET)"
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET)_debug

help:
	@echo "Available commands:"
	@echo "  all     - Build with optimizations (-O2)"
	@echo "  debug   - Build with debugging information (-g -O0)"
	@echo "  run     - Run program"
	@echo "  clean   - Remove all generated files"
	@echo "  help    - Show help message"
	@echo ""
	@echo "Compiler flags:"
	@echo "  Release: $(CFLAGS_RELEASE)"
	@echo "  Debug:   $(CFLAGS_DEBUG)"

# Dependencies
main.o: main.c list.h
list.o: list.c list.h