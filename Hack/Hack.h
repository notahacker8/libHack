
#include <mach-o/dyld.h>
#include <mach-o/dyld_images.h>

#define base() (0x100000000 + _dyld_get_image_vmaddr_slide(0))





typedef struct vector3 {
    float x;
    float y;
    float z;
} vector3_t;




///The CFrame structure in memory for Roblox.
typedef struct rbx_cframe {
    float r0;
    float r1;
    float r2;
    float r10;
    float r11;
    float r12;
    float r21;
    float r22;
    vector3_t position;
} rbx_cframe_t;


struct rbx_local_player_values {
    char unknown0[0xb8];
    float gravity;
    char unknown1[4];
    rbx_cframe_t player_cframe;
};






struct head_soccer_character_stats {
    int speed;
    int kick;
    int jump;
    int dash;
    int power;
    int survival;
};

struct head_basketball_character_stats {
    int swing;
    int speed;
    int dash;
    int jump;
    int strength;
    int ep_regen;
    int survival;
};


struct ac_player_values {
    char unknown0[8];
    vector3_t coordinates;
    char unknown1[24];
    float yaw;
    float pitch;
};
