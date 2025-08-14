# Declare phony targets
.PHONY: all clean help area sqrt log

CC := gcc
CFLAGS := -Wall -Wextra -g
# Automatically find all C source files in current directory
SOURCES := $(wildcard *.c)

OBJECTS := $(SOURCES:.c=.o)     # area.o sqrt.o log.o
TARGETS := $(SOURCES:.c=.out)   
PROGRAMS := $(SOURCES:.c=)      

# Default target => input make will run make all
all: $(TARGETS)

# Static pattern rule: Compile C source files to object files
# Syntax: $(targets): target-pattern: prereq-pattern
$(OBJECTS): %.o: %.c
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Static pattern rule: Link object files to create executables
$(TARGETS): %.out: %.o
	@echo "Linking $< to create $@"
	@$(CC) $< -o $@ -lm

# Static pattern rule: Run programs (allows 'make area', 'make sqrt', etc.)
$(PROGRAMS): %: %.out
	@echo "Running $< program:"
	@./$<

# ./ = current directory
# @ can suppress the command output

# Clean
clean:
	@echo "Cleaning up generated files"
	@rm -f $(TARGETS) $(OBJECTS)
	@echo "Done."

# Help target
help:
	@echo "Available targets:"
	@echo "  all   - Build all executables"
	@echo "  clean - Remove generated files (.out and .o)"
	@echo "  help  - Show this help message"
	@echo ""
	@echo "Program-specific targets:"
	@for PROGRAMS in $(PROGRAMS); do \
		echo "  $$PROGRAMS - Build & run $$PROGRAMS.out executable"; \
	done