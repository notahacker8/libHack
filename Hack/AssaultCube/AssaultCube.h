


typedef struct
{
    char __unknown0[0x8];       // + 0x0
    vector3_t position;         // + 0x8
    char __unknown1[0x30];      // + 0x14
    float yaw;                  // + 0x44
    float pitch;                // + 0x48
    char __unknown2[0xc4];      // + 0x4C
    int health;                 // + 0x110
    char __unknown3[0x234];     // + 0x114
    int team_num;               // + 0x348
}
ac_player_values_t;



void* assaultcube_hack(void* arg)
{
    
    void** entity_list_ptr = (void**)(base() + 0x1ABF10);
    int* entity_count_ptr = (int*)(base() + 0x1ABF1C);
    
    static ac_player_values_t** entity_list = NULL;
    static ac_player_values_t* target_player = NULL;
    ac_player_values_t* my_player = *(void**)(base() + 0x1ABF08);
    
    
    //So we can have "infinite ammo".
    char* ammo_decrementer = (char*)(base() + 0x103F6F);
    mach_vm_protect(mach_task_self_, (mach_vm_address_t)ammo_decrementer, 2, FALSE, VM_PROT_ALL);
    ammo_decrementer[0] = 0x90;
    ammo_decrementer[1] = 0x90;
    
    
    for (;;) {
        usleep(2000);
        entity_list = *entity_list_ptr;
        my_player->health = 999;
        if (entity_list != NULL)
        {
            target_player = NULL;
            static float aimbot_dist = 50;
            for (int i = 1 ; i < *entity_count_ptr ; i++)
            {
                float dist_dif = vector3_dist_dif(my_player->position, entity_list[i]->position);
                if (dist_dif < aimbot_dist && entity_list[i]->health > 0 &&
                    entity_list[i]->team_num != my_player->team_num)
                {
                    target_player = entity_list[i];
                    aimbot_dist = dist_dif;
                }
            }
            aimbot_dist = 100;
            if (target_player != NULL && target_player->health > 0)
            {
                if (target_player->team_num != my_player->team_num)
                {
                    vector3_t pos_dif = vector3_sub(target_player->position, my_player->position);
                    float dist_dif = vector3_dist_dif(target_player->position, my_player->position);
                    my_player->pitch = (asinf((pos_dif.z) / dist_dif) * 180.0f/PI);
                    my_player->yaw = fmodf((atan2f(pos_dif.y, pos_dif.x) * 180/PI) + 90, 360);
                }
            }
        }
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    return NULL;
}


