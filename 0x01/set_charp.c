#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int ft_check_args(int argc, char **argv) {
    if (argc != 3 || !isdigit(*argv[1])) {
        printf("Usage: %s <pidof dummy> <address of the character pointer>", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(void) {
    /* Check arguments for bad input */
    /*ft_check_args(argc, argv);*/

    int fd;
    char file[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    /* Set pid variable to the first argument */
    long pid;
    printf("Enter the PID of the target process: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%ld", &pid);

    /* Set the address of the character pointer (in hexadecimal) */
    unsigned long pointer_address;
    printf("Enter the address of the character pointer (in hexadecimal): ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%lx", &pointer_address);

    /* Set the value you want to set at the pointer's location */
    char new_char;
    printf("Enter the new character value: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%c", &new_char);

    /* Open the virtual file mem, that is a view of that process' entire address space, including unmapped regions */
    sprintf(file, "/proc/%ld/mem", pid);
    if ((fd = open(file, O_RDWR)) == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    /* Attach to the process */
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);

    /* Wait for the process */
    if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return EXIT_FAILURE;
    }

    /* Read the character pointer's value */
    unsigned long char_address = ptrace(PTRACE_PEEKDATA, pid, pointer_address, NULL);
    /* Read the character pointer's value */
    char original_value = ptrace(PTRACE_PEEKDATA, pid, char_address, NULL);

    /* Write the new character value to the location pointed to by the character pointer */
    if (ptrace(PTRACE_POKEDATA, pid, char_address, new_char) == -1) {
        perror("ptrace");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    if (ptrace(PTRACE_POKEDATA, pid, pointer_address, char_address) == -1) {
        perror("ptrace");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    /* Detach from the process and close the file */
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    close(fd);

    printf("Changed the value %c pointed by the character pointer at address %lx to %c\n", original_value, pointer_address, new_char);

    return EXIT_SUCCESS;
}
