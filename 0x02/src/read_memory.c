#include <read_memory.h>

int read_memory(unsigned long address, unsigned long *destination, unsigned int pid) {
    long return_value;

    int err_code;

    err_code = ptrace(PTRACE_ATTACH, pid, NULL, NULL);

    if (err_code == -1) {
        perror("ptrace");
        return EXIT_FAILURE;
    }

    /* Wait for the process */
    if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return EXIT_FAILURE;
    }

    return_value = ptrace(PTRACE_PEEKDATA, pid, address, NULL);

    if (return_value == -1) {
        perror("ptrace");
        return EXIT_FAILURE;
    }

    err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);

    if (err_code == -1) {
        printf("Error we can't peak data \n");
        return EXIT_FAILURE;
    }

    *destination = return_value;

    return EXIT_SUCCESS;
}
