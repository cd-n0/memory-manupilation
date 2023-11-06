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
    printf("Usage: %s <pidof dummy> <address of the character variable> <Value "
           "you want>",
           argv[0]);

    exit(EXIT_FAILURE);
  }
  return 0;
}

int main(void) {
    /* Check arguments for bad input */
    /*ft_check_args(argc, argv);*/

    /* Set pid variable to the first argument */
    /*long pid = atoi(argv[1]);*/

    /* Set the address of the variable we want to change */
    /*off_t address = strtol(argv[2], NULL, 16);*/
    /* Set the value we want to change it to */
    /*int value = atoi(argv[3]);*/

    int fd;
    char file[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    /* Set pid variable to the first argument */
    long pid;
    printf("Enter the PID of the target process: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%ld", &pid);
    
    /* Set the address of the variable we want to change */
    off_t char_address;
    printf("Enter the address of the character variable (in hexadecimal): ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%lx", &char_address);

    /* Set the value we want to change it to */
    char new_char;
    printf("Enter the new character value: ");
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%c", &new_char);

    /* Open the virtual file mem, that is a view of that process' entire address
     * space, including unmapped regions */
    sprintf(file, "/proc/%ld/mem", pid);
    /* Check if open was successful, if not write an error message then return
     * -1 */
    if ((fd  = open(file, O_RDWR)) == -1)
    {
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

    /* Read from memory */
    char original_value = ptrace(PTRACE_PEEKDATA, pid, char_address, NULL);
    if (original_value == -1) {
        perror("ptrace");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        exit(EXIT_FAILURE);
    }
    /* Write it to the memory */
    if (ptrace(PTRACE_POKEDATA, pid, char_address, new_char) == -1) {
        perror("ptrace");
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    /* Detach from process and close file */
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    close(fd);
    printf("Changed memory address %lx from %c to %c\n", char_address, original_value, new_char);

    return EXIT_SUCCESS;
}
