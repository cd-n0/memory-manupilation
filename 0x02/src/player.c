#include <read_memory.h>
#include <write_memory.h>
#include <player.h>

unsigned long local_player_address;
pid_t pid;

int player_local_info(t_player *player, unsigned long module, unsigned int process_id) {
    pid = process_id;
    read_memory(module + player_offset, &local_player_address, pid);
    read_memory(local_player_address + hp_offset, (unsigned long*)&(player->hp), pid);
    read_memory(local_player_address + assault_rifle_clip_offset, (unsigned long*)&(player->assault_rifle_clip), pid);

    return EXIT_FAILURE;
}

void display_player_coordinates(t_player *player) {
    printf("Player position [x:%f, y:%f, z:%f]\n", player->x, player->y, player->z);
}

void display_player_hp(t_player *player) {
    printf("Player HP: %d\n", player->hp);
}
void set_player_hp(const int32_t value) {
    write_memory(local_player_address + hp_offset, (void *)&value, sizeof(int32_t), pid);
}

void display_player_assault_rifle_clip(t_player *player) {
    printf("Player MG Clip: %d\n", player->assault_rifle_clip);
}
void set_player_assault_rifle_clip(const int32_t value) {
    write_memory(local_player_address + assault_rifle_clip_offset, (void *)&value, sizeof(int32_t), pid);
}

void display_player_bomb(t_player *player) {
    printf("Player Bomb: %d\n", player->bomb);
}
void set_player_bomb(const int32_t value) {
    write_memory(local_player_address + bomb_offset, (void *)&value, sizeof(int32_t), pid);
}
