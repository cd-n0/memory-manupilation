#include <write_memory.h>

int write_memory(unsigned long addr, void* data, size_t size, unsigned int pid) {
    int err_code = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
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


    // Write data in chunks
    size_t bytes_written = 0;
    while (bytes_written < size) {
        unsigned char value = 0;
        memcpy(&value, (unsigned char*)data + bytes_written, sizeof(char));

        long ret = ptrace(PTRACE_POKEDATA, pid, addr + bytes_written, value);

        if (ret == -1) {
            perror("ptrace");
            return EXIT_FAILURE;
        }

        bytes_written += sizeof(char);
    }

    err_code = ptrace(PTRACE_DETACH, pid, NULL, NULL);

    if (err_code == -1) {
        printf("Error detaching from the process\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

