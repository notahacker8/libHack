


typedef struct
{
    int speed;
    int kick;
    int jump;
    int dash;
    int power;
    int survival;
}
hs_character_stats_t;




void* head_soccer_hack(void* arg) {
    static int character_count = 86;
    static int stats_size = sizeof(hs_character_stats_t);
    
    int* total_points = (int*)(base() + 0x7CF590);
    int* first_stats = (int*)(base() + 0x731EC0);
    int* left_survival_balls = (int*)(base() + 0x722C20);
    int* right_survival_balls = (int*)((long)left_survival_balls + sizeof(int));
    int* survival_stage_count = (int*)(base() + 0x7D2A38);
    
    for (;;)
    {
        usleep(10000);
        
        for (int i = 0 ; i < character_count ; i++)
        {
            hs_character_stats_t* stats = (void*)(first_stats + (i * stats_size));
            stats->speed = 20;
            stats->kick = 20;
            stats->jump = 20;
            stats->dash = 20;
            stats->power = 20;
            stats->survival = 20;
        }
        
        *left_survival_balls = 20;
        *right_survival_balls = 0;
        *survival_stage_count = 100;
        *total_points = 399999999;
    }
    return NULL;
}


