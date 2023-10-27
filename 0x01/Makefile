CC = gcc
CFLAGS = -std=c89 -Wall -Wextra -Werror 

all: dummy_program set_int set_intp

dummy_program: dummy_program.c
	$(CC) $(CFLAGS) -o $@ $<

set_int: set_int.c
	$(CC) $(CFLAGS) -o $@ $<

set_intp: set_intp.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f dummy_program set_int set_intp

.PHONY: all clean
