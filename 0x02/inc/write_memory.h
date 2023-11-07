#ifndef WRITE_MEMORY_H
#define WRITE_MEMORY_H

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

int write_memory(unsigned long addr, void* data, size_t size, unsigned int pid);

#endif /* WRITE_MEMORY_H */
