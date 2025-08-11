# prevent thses targets from being confused with files
.PHONY: all run clean help

# CC = gcc
ifndef CC
    CC = gcc
endif

CFLAGS = -Wall -O2 -std=c99

all: hello.out

hello.out: hello.o
	$(CC) $(CFLAGS) -o hello.out hello.o

hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c

run: hello.out
	./hello.out

# rm -f => $(RM)
clean:
	rm -f hello.o hello.out

help:
	@echo " These are available targets:"
	@echo " make all   - Build hello.out from hello.c"
	@echo " make run   - Run the hello.out executable"
	@echo " make clean - Remove generated object files and executable"
	@echo " make help  - Show this help message"