#ifndef READ_MEMORY_H
#define READ_MEMORY_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define MEM_INIT 0

int read_memory(unsigned long address, unsigned long *destination, unsigned int pid);

#endif /* READ_MEMORY_H */
