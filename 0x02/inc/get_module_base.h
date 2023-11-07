#ifndef MODULE_BASE
#define MODULE_BASE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE         1024
#define FIRST_LINE_SIZE     13
#define ADDRESS_OFFSET      12
#define INITIALIZE_MEMORY   0

typedef struct s_get_modulebase {
    char file_maps[BUFFER_SIZE];
    char line[BUFFER_SIZE];
    char get_first_line[FIRST_LINE_SIZE];
    char real_module[ADDRESS_OFFSET];

    unsigned long convert_module;

    FILE *get_module_base_address_file;
} t_base_address;

extern t_base_address local_player_address;

unsigned long get_module_base(const char *module);

#endif
