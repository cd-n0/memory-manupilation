#include <cdnull.h>
#include <unistd.h>

#define DESIRED_HP 420
#define DESIRED_MG_CLIP 69
#define DESIRED_BOMB 5

int main(void) {
    unsigned int pid;
    unsigned long module;

    t_player player;

    pid = get_pid("linux_64_client");
    module = get_module_base("linux_64_client");

    printf("Module is : %lx\n", module);

    while (errno == 0) {
        printf("\x1b[2J"); // Clear the screen
        printf("\x1b[H"); // Move the cursor to the home position
        player_local_info(&player, module, pid);
        //player_display_coordinates(&player);
        display_player_hp(&player);
        if (player.hp < DESIRED_HP)
            set_player_hp(DESIRED_HP);
        display_player_assault_rifle_clip(&player);
        if (player.assault_rifle_clip < DESIRED_MG_CLIP)
            set_player_assault_rifle_clip(DESIRED_MG_CLIP);
        display_player_bomb(&player);
        if (player.bomb < DESIRED_BOMB)
            set_player_bomb(DESIRED_BOMB);
        /* Sleep for tenth of a milisecond to reduce reads/writes */
        usleep(10000);
    }

    return 0;

}
    
    
