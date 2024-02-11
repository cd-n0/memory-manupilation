#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t
get_pid_by_name(char* pid_name)
{
    struct dirent* entry;
    char command[BUFFER_SIZE];
    char cmdline[BUFFER_SIZE];
    pid_t pid = -1;
    DIR* dir = opendir("/proc");

    /* Open /proc directory */
    if (dir == NULL) {
        fprintf(stderr, "Failed to open /proc directory\n");
        return -1;
    }

    while (pid == -1) {
        /* Look inside /proc/<pid>/cmdline directories until we find the name inside one of the cmdlines */
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && atoi(entry->d_name) > 0) {
                snprintf(command, BUFFER_SIZE, "/proc/%s/cmdline", entry->d_name);

                FILE* fd = fopen(command, "r");
                if (fd == NULL) {
                    perror("fopen");
                    continue;
                }

                fgets(cmdline, BUFFER_SIZE, fd);
                fclose(fd);

                if (strstr(cmdline, pid_name) != NULL) {
                    pid = atoi(entry->d_name);
                    break;
                }
            }
        }


        /* If we can't find the process print an error message and retry */
        if (pid == -1) {
            fprintf(stderr, "No process found with name %s\n", pid_name);
            printf("Retrying in 3 seconds\n");
            rewinddir(dir);
            sleep(3);
        }
    }

    closedir(dir);

    return pid;
}

uintptr_t
get_base_module(char *module){
    pid_t pid;
    char maps_file[BUFFER_SIZE];
    char *ptr = NULL;
    ssize_t status;
    size_t i;
    if (module == NULL)
        return 0;
    pid = get_pid_by_name(module);
    snprintf(maps_file, BUFFER_SIZE, "/proc/%d/maps", pid);

    /* 
       Why we need to read with syscalls -> https://stackoverflow.com/questions/8992430/any-idea-why-my-c-code-cant-read-from-proc
       size_t file_size;
       FILE *fp;

       fp = fopen(maps_file, "r");
       if (fp == NULL) {
       perror("Error opening file");
       return NULL;
       }

       fseek(fp, 0, SEEK_END);
       file_size = ftell(fp);
       rewind(fp);

       char *maps_buffer = (char *)malloc(file_size * sizeof(char));
       if (maps_buffer == NULL) {
       perror("Error allocating memory");
       return NULL;
       }

       fread(maps_buffer, file_size, sizeof(char), fp);

       char *base_address = (char *)calloc(1000, sizeof(char));
       if (maps_buffer == NULL) {
       perror("calloc");
       return NULL;
       }

       printf("%s\n", maps_buffer);
       */

    int fd = open(maps_file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 0;
    }

    char *maps_buffer = (char *)calloc(10000, sizeof(char));
    if (maps_buffer == NULL) {
        perror("calloc");
        return 0;
    }

    char *base_address = (char *)calloc(100, sizeof(char));
    if (base_address == NULL) {
        perror("calloc");
        return 0;
    }

    for (i = 0, status = 1;  status != 0 && status != -1 && i < BUFFER_SIZE ; i++){
        status = read(fd, maps_buffer + i, 1);
    }

    if (module != NULL) {
        if ((ptr = strstr(maps_buffer, module)) == NULL) {
            fprintf(stderr, "Failed to find module!\n");
            return 0;
        }
    } 

    else {
        /* readable executable private mapping */
        if ((ptr = strstr(maps_buffer, "r-xp")) == NULL) {
            fprintf(stderr, "Failed to find memory module!\n");
            return 0;
        }
    }

    while (*ptr != '\n' && maps_buffer < ptr) {
        ptr--;
    }
    ptr++;

    for (i = 0; *ptr != '-'; i++) {
        base_address[i] = *ptr;
        ptr++;
    }

    uintptr_t module_base = strtol(base_address, NULL, 16);

    free(maps_buffer);
    free(base_address);
    return module_base;
}
