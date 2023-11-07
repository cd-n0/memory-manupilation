#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

// These offsets are for AssaultCube v1.3.0.2 Lockdown-Edition
// Check the sums for binary linux_64_client inside bin_unix
// md5: ceb8b79f0bbcaad9ae77835ee79ddd41
// sha256: f8209caa52644069f056421fd2488be5ab018293773f138651c7602ba68cb228
#define player_offset 0x1A3518
//#define y_position_offset 0xDEADBEEF
//#define x_position_offset 0xDEADBEEF
//#define z_position_offset 0xDEADBEEF
#define hp_offset 0x100
#define armor_offset 0x104
#define pistol_ammo_offset 0x11C
#define carbine_ammo_offset 0x120
#define shotgun_ammo_offset 0x124
#define smg_ammo_offset 0x128
#define sniper_ammo_offset 0x12C
#define assault_rifle_ammo_offset 0x130
#define akimbo_ammo_offset 0x138

#define pistol_clip_offset 0x140
#define carbine_clip_offset 0x144
#define shotgun_clip_offset 0x148
#define smg_clip_offset 0x14C
#define sniper_clip_offset 0x150
#define assault_rifle_clip_offset 0x154
#define bomb_offset 0x158
#define akimbo_clip_offset 0x15C

typedef struct s_player {
    float x;
    float y;
    float z;
    int hp;
    int armor;
    int assault_rifle_clip;
    int assault_rifle_ammo;
    int smg_clip;
    int smg_ammo;
    int sniper_clip;
    int sniper_ammo;
    int shotgun_clip;
    int shotgun_ammo;
    int carbine_clip;
    int carbine_ammo;
    int bomb;
} t_player;

int player_local_info(t_player *player, unsigned long module, unsigned int pid);
//void display_player_coordinates(t_player *player);
void display_player_hp(t_player *player);
void set_player_hp(int32_t value);
void display_player_assault_rifle_clip(t_player *player);
void set_player_assault_rifle_clip(int32_t value);
void display_player_bomb(t_player *player);
void set_player_bomb(int32_t value);
#endif
