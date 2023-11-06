CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -Werror 
TARGETS = dummy_program set_int set_intp set_charp set_char

all: $(TARGETS)

dummy_program: dummy_program.c
	$(CC) $(CFLAGS) -o $@ $<

set_int: set_int.c
	$(CC) $(CFLAGS) -o $@ $<

set_intp: set_intp.c
	$(CC) $(CFLAGS) -o $@ $<

set_char: set_char.c
	$(CC) $(CFLAGS) -o $@ $<

set_charp: set_charp.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

.PHONY: all clean
