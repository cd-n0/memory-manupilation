#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
 
int write_memory_offsets(int mem_fd, uintptr_t base_address, size_t length, void *data_buffer, int num_offsets, ...);
int write_memory(pid_t pid, uintptr_t address, size_t length, void *data_buffer);
uintptr_t read_memory(pid_t pid, uintptr_t address, size_t length);
int open_mem_file(pid_t pid);
void close_mem_file(int mem_fd);
