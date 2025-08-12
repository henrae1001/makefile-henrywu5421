# Declare phony targets
.PHONY: all clean help area sqrt log

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_GNU_SOURCE
SOURCES = $(wildcard *.c)
TARGETS = $(SOURCES:.c=.out)
PROGRAMS = area sqrt log

# Default target
all: $(TARGETS)

# Pattern rule to build executables from C source files
%.out: %.c
	$(CC) $(CFLAGS) -o $@ $< -lm

# Targets to build and run specific programs
area: area.out
	@echo "Running area program:"
	@./area.out

sqrt: sqrt.out
	@echo "Running sqrt program:"
	@./sqrt.out

log: log.out
	@echo "Running log program:"
	@./log.out

# Clean target to remove generated files
clean:
	@echo "Cleaning up generated files"
	@rm -f $(TARGETS)
	@echo "Done"

# Help target
help:
	@echo "Available targets:"
	@echo "  all   - Build all executables"
	@echo "  clean - Remove generated files"
	@echo "  help  - Show this help message"
	@echo "  area  - Build & run the area.out executable"
	@echo "  sqrt  - Build & run the sqrt.out executable"
	@echo "  log   - Build & run the log.out executable"
	@echo ""
	@echo "Generated executables: $(TARGETS)"
