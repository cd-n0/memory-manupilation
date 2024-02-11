#include "module.h"
#include "offsets.h"
#include "memory.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int stop = 0;

void sigint_handler(int signal){
    if (signal == SIGINT){
        printf("Got signal SIGINT, exiting\n");
        stop = 1;
    }
    return;
}

void set_signal_action(void){
    struct sigaction act;
    act.sa_handler = &sigint_handler;
    sigaction(SIGINT, &act, NULL);
    return;
}

int
main(int argc, char *argv[]){
    set_signal_action();
    if (argc != 2 || argv[1] == NULL){
        fprintf(stderr, "Usage: %s <assault_cube_binary_name>(probably linux_64_client)", argv[0]);
        exit(EXIT_FAILURE);
    }
    pid_t pid = get_pid_by_name(argv[1]);
    printf("PID of AC: %d\n", pid);
    uintptr_t module_base = get_base_module(argv[1]);
    printf("Module base address: 0x%lx\n", module_base);
    int mem_fd = open_mem_file(pid);
    int hp_value = 1000;
    int ammo_value = 10;
    while (!stop) {
        write_memory(mem_fd, read_memory(mem_fd ,module_base + PLAYER_OFFSET, sizeof(void*)) + HP_OFFSET, sizeof(int), &hp_value);
        write_memory_offsets(mem_fd, module_base, sizeof(int), &ammo_value, 3, PLAYER_OFFSET, CURRENT_WEAPON_CLIP_OFFSETS[0], CURRENT_WEAPON_CLIP_OFFSETS[1]);
        usleep(100);
        if (kill(pid, 0) == -1)
            break;
    }
    close_mem_file(mem_fd);

    return 0;
}
