#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int ft_check_args(int argc, char **argv){
  if (argc != 4 || !isdigit(*argv[1]) || !isxdigit(*argv[2]) ||
      !isdigit(*argv[3])) {
    printf("Usage: %s <pidof dummy> <address of the integer variable> <Value "
           "you want>",
           argv[0]);

    exit(EXIT_FAILURE);
  }
  return 0;
}

int main(int argc, char *argv[]) {
    /* Check arguments for bad input */
    /*ft_check_args(argc, argv);*/

    /* Set pid variable to the first argument */
    /*long pid = atoi(argv[1]);*/
    argc = argc;

    int fd;
    char file[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    /* Set pid variable to the first argument */
    long pid;
    printf("Enter the PID of the target process: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%ld", &pid);
    
    /* Set the address of the variable we want to change */
    off_t int_address;
    printf("Enter the address of the integer variable (in hexadecimal): ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%lx", &int_address);

    /* Set the value we want to change it to */
    int new_value;
    printf("Enter the new integer value: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &new_value);

    /* Open the virtual file mem, that is a view of that process' entire address
     * space, including unmapped regions */
    sprintf(file, "/proc/%ld/mem", pid);
    /* Check if open was successful, if not write an error message then return
     * -1 */
    if ((fd  = open(file, O_RDWR)) == -1)
    {
    printf("Usage: %s <pidof dummy> <address of the integer variable> <Value "
           "you want>",
           argv[0]);
        perror("open");
        return EXIT_FAILURE;
    }

    /* Attach to the process */
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    /* Wait for the process */
    if (waitpid(pid, NULL, 0) == -1) {
    printf("Usage: %s <pidof dummy> <address of the integer variable> <Value "
           "you want>",
           argv[0]);
        perror("waitpid");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return EXIT_FAILURE;
    }

    /* Set the address of the variable we want to change */
    /*off_t address = strtol(argv[2], NULL, 16);*/
    /* Set the value we want to change it to */
    /*int value = atoi(argv[3]);*/

    /* Read from memory */
    int original_value = ptrace(PTRACE_PEEKDATA, pid, int_address, NULL);
    if (original_value == -1) {
        perror("ptrace");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        exit(EXIT_FAILURE);
    }
    /* Write it to the memory */
    if (ptrace(PTRACE_POKEDATA, pid, int_address, new_value) == -1) {
        perror("ptrace");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    /* Detach from process and close file */
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    close(fd);
    printf("Changed memory address %lx from %d to %d\n", int_address, original_value, new_value);

    return EXIT_SUCCESS;
}
