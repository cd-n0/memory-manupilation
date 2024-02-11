#include "memory.h"

static void
print_hex(const char* buffer, size_t size) {
    size_t i;
    for (i = 0; i < size; ++i) {
        printf("%02X", (uint8_t)buffer[i]);
    }
    printf("\n");
}

static char*
convert_to_hex_string(const char* buffer, size_t size) {
    size_t i;
    char* ret = (char*)malloc((size * 2 + 1) * sizeof(char));  /* Each byte represented by 2 characters, plus '\0' at the end */

    if (ret == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < size; ++i) {
        sprintf(ret + i * 2, "%02X", (uint8_t)buffer[i]);
    }

    ret[size * 2] = '\0';  /* Null-terminate the string */

    return ret;
}

static void
check_permission(void){
    if (getuid() != 0){
        fprintf(stderr, "Insufficient permissions, try running as root or sudo\n");
        exit(EXIT_FAILURE);
    }
    return;
}

/* Function to open the mem file */
int open_mem_file(pid_t pid) {
    check_permission();

    char proc_mem[100];
    snprintf(proc_mem, 100, "/proc/%d/mem", pid);
    
#if DEBUG_PRINT
    printf("opening %s\n", proc_mem);
#endif

    int mem_fd = open(proc_mem, O_RDWR);
    
    if (mem_fd == -1) {
        fprintf(stderr, "Could not open %s\n", proc_mem);
        perror("open");
        exit(EXIT_FAILURE);
    }
    return mem_fd;
}

/* Function to close the mem file */
void close_mem_file(int mem_fd) {
    if (mem_fd != -1) {
        close(mem_fd);
    }
}

int
write_memory_offsets(int mem_fd, uintptr_t base_address, size_t length, void *data_buffer, int num_offsets, ...) {
    size_t i;
    uintptr_t address = base_address;
    va_list offsets;
    va_start(offsets, num_offsets);

    for (i = 0; i < num_offsets; ++i) {
        address = read_memory(mem_fd, address + va_arg(offsets, int), sizeof(void*));
    }

    va_end(offsets);

    return write_memory(mem_fd, address, length, data_buffer);
}

int
write_memory(int mem_fd, uintptr_t address, size_t length, void *data_buffer){
    char* mem_buffer = malloc(length);
    if (mem_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    lseek(mem_fd, address, SEEK_SET);
    read (mem_fd, mem_buffer , length);

#if DEBUG_PRINT
    printf("Data at %lx is:\n", address);
    print_hex(mem_buffer, length);
#endif

    memcpy(mem_buffer, data_buffer, length);

    lseek(mem_fd, address, SEEK_SET);
    if (write (mem_fd, mem_buffer , length) == -1) {
        fprintf(stderr, "Error while writing\n");
        perror("write");
        return 1;
    }

#if DEBUG_PRINT
    printf("Now, the data is modified\n");
#endif

    free(mem_buffer);
    return 0;
}

uintptr_t
read_memory(int mem_fd, uintptr_t address, size_t length){
    char* mem_buffer = malloc(length);
    if (mem_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    lseek(mem_fd, address, SEEK_SET);
    read (mem_fd, mem_buffer , length);

    /* We need to flip the data if it's little endian */
    if (LITTLE_ENDIAN){
        size_t i;
        for (i = 0; i < length / 2; ++i) {
            char temp = mem_buffer[i];
            mem_buffer[i] = mem_buffer[length - i - 1];
            mem_buffer[length - i - 1] = temp;
        }
    }

#if DEBUG_PRINT
    printf("Data at %lx is:\n", address);
    print_hex(mem_buffer, length);
#endif

    char *old_buffer = mem_buffer;
    mem_buffer = convert_to_hex_string(mem_buffer, length);

    uintptr_t value = strtol(mem_buffer, NULL, 16);

    free(old_buffer);
    free(mem_buffer);

    return value;
}
