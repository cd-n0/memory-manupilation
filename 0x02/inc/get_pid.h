#ifndef GET_PID_H
#define GET_PID_H

#include <stdio.h>
#include <stdlib.h>


#define BUFFER_SIZE 1024

typedef struct s_stock_pid {
    pid_t pid;
    char buffer[BUFFER_SIZE];
    char pid_buffer[BUFFER_SIZE];
    FILE *pid_pipe;

} t_process_pid;

extern t_process_pid process_pid;

unsigned int get_pid(const char *targetprocess);

#endif /* GET_PID_H */
