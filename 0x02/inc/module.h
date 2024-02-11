#ifndef MODULE_H
#define MODULE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>

#define BUFFER_SIZE 2048

pid_t
get_pid_by_name(char* pid_name);

uintptr_t
get_base_module(char *module);

#endif /* MODULE_H */
