#include <get_pid.h>

t_process_pid process_pid;

unsigned int get_pid(const char *targetprocess) {
    sprintf(process_pid.pid_buffer, "pidof -s %s", targetprocess);
    process_pid.pid_pipe = popen(process_pid.pid_buffer, "r");
    fgets(process_pid.buffer, BUFFER_SIZE, process_pid.pid_pipe);
    process_pid.pid = strtoul(process_pid.buffer, NULL, 10);

    if (process_pid.pid == 0) {
      printf("Couldn't find the pid, if you are sure that the process is "
             "running, replace the pid in main.c\n");
      pclose(process_pid.pid_pipe);
      exit(EXIT_FAILURE);
    } else {
        pclose(process_pid.pid_pipe);
    }

    return process_pid.pid;
}
