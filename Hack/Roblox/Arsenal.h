

/*
void rbx_arsenal_hack()
{
    
    
    
#pragma mark -
#pragma mark Globals
    
    
    
    static vm_offset_t service_count = 0;
    
    rbx_humanoid_class_methods_t* humanoid_class_methods = rbx_get_humanoid_class_methods();
    rbx_r_float_p_class_f* rbx_get_humanoid_health = NULL; //(rbx_r_float_p_class_f*)(humanoid_class_methods -> health_setter);
    
    rbx_instance_t* game = rbx_get_game_instance();
    rbx_instance_t** services = rbx_get_children((void*)game, &service_count);
    
    rbx_instance_t* workspace = (void*)services[__RBX_WORKSPACE_SERVICE_INDEX__];
    rbx_instance_t* players = (void*)services[__RBX_PLAYERS_SERVICE_INDEX__];
    static const int max_players = 16;
    
    rbx_camera_t* camera = rbx_get_current_camera(workspace);
    rbx_player_t* local_player = rbx_get_local_player(players);
    
    const static float max_node_ratio = 0.2;
    
    static bool closest_enemy_exists = false;
    static bool aimbot_on = false;
    
    static rbx_part_t* closest_enemy_head;
    static vector3_t new_look_vector;
    
    static const float y_limit = -400.0f;
    
    
    
#pragma mark -
#pragma mark ESP
    
    
    
    
    static NSSize window_size;
    static NSView* rbx_ogre_view;
    
    
    
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseDown handler:^NSEvent * _Nullable(NSEvent * _Nonnull event)
    {
        aimbot_on = true;
        return event;
    }];
    
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseUp handler:^NSEvent * _Nullable(NSEvent * _Nonnull event)
    {
        aimbot_on = false;
        return event;
        
    }];
    
    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^
    {
        for (;;)
        {
            dispatch_async(dispatch_get_main_queue(), ^
            {
                window_size = NSApp.windows[0].contentView.frame.size;
                rbx_ogre_view = NSApp.windows[0].contentView.subviews[0];
            });
            sleep(1);
        }
    });
    
    
    sleep(1);
    
    
    void** esp_box_array = allocate_blank_esp_box_array(rbx_ogre_view, max_players);
    void** esp_text_array = allocate_blank_esp_text_array(rbx_ogre_view, max_players);
    void** player_name_array = malloc(sizeof(void*) * max_players);
    
    for (register unsigned short i = 0 ; i < max_players ; i++)
    { player_name_array[i] = malloc(__RBX_MAX_PLAYER_NAME_LENGTH__); }
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^
    { for (;;) { refresh_esp_view_array(esp_box_array, 0, max_players, 3000); } });
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^
    { for (;;) { refresh_esp_view_array(esp_text_array, 0, max_players, 3000); } });
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^
    {
        static vm_offset_t player_count;
        NSColor* esp_text_color = NSColor.orangeColor;
        for (;;)
        {
            rbx_player_t** player_list = (rbx_player_t**)rbx_get_children((void*)players, &player_count);
            for (vm_offset_t i = 0 ; i < player_count ; i++)
            {
                const rbx_player_t* player = player_list[i];
                if (player != NULL && player != local_player)
                {
                    rbx_instance_t* my_character = local_player -> character;
                    if (my_character != NULL)
                    {
                        rbx_instance_t* my_hum = (void*)rbx_find_first_child_of_class(my_character, "Humanoid");
                        if (my_hum != NULL)
                        {
                        }
                    }
                    
                    if (player -> team != local_player -> team || local_player -> team == NULL)
                    {
                        bzero(player_name_array[i], __RBX_MAX_PLAYER_NAME_LENGTH__);
                        strcpy(player_name_array[i], ((rbx_instance_t*)player) -> name + 1);
                        const rbx_instance_t* character = player -> character;
                        if (character != NULL)
                        {
                            const rbx_part_t* head = (void*)rbx_find_first_child(character, "Head");
                            if (head != NULL)
                            {
                                const vector3_t head_pos =  head -> properties -> cframe.pos;
                                if (head_pos.y > y_limit) {
                                    custom_rbx_world_to_screen_info_t wtsi = rbx_world_to_screen_point(camera, head_pos, window_size);
                                    NSPoint point = wtsi.point;
                                    dispatch_async(dispatch_get_main_queue(), ^
                                    {
                                        NSView* esp_box = (__bridge NSView*)esp_box_array[i];
                                        NSTextField* esp_text = (__bridge NSTextField*)esp_text_array[i];
                                        const char* player_name = player_name_array[i];
                                        
                                        if (is_valid_point(point) == true)
                                        {
                                            esp_box.hidden = NO;
                                            esp_box.frame = NSMakeRect(point.x - 10, point.y + 30, 20, 20);
                                            esp_box.layer.borderColor = esp_text_color.CGColor;
                                            
                                            esp_text.hidden = NO;
                                            esp_text.frame = NSMakeRect(point.x - 100, point.y + 60, 200, 30);
                                            esp_text.textColor = esp_text_color;
                                            esp_text.stringValue = [NSString stringWithUTF8String: player_name];
                                        }
                                        else
                                        {
                                            esp_text.hidden = YES;
                                            esp_box.hidden = YES;
                                        }
                                    });
                                }
                            }
                        }
                    }
                }
            }
            usleep(1500);
            free(player_list);
        }
    
    });
    
    
    
    
#pragma mark -
#pragma mark Aimbot
    
    
    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        for (;;)
        {
            bool cee = false;
            float old_dist = 999999;
            static vm_offset_t player_count = 0;
            rbx_player_t** player_list = (rbx_player_t**)rbx_get_children((void*)players, &player_count);
            for (vm_offset_t i = 0 ; i < player_count ; i++)
            {
                const vector3_t camera_pos = camera -> cframe_1.pos;
                const vector3_t camera_look_vector = rbx_get_cframe_look_vector(camera -> cframe_1);
                const rbx_player_t* player = player_list[i];
                
                if (player != NULL && player != local_player)
                {
                    if (player -> team != local_player -> team || local_player -> team == NULL)
                    {
                        const rbx_instance_t* character = player -> character;
                        if (character != NULL)
                        {
                            rbx_part_t* head = (void*)rbx_find_first_child(character, "Head");
                            if (head != NULL)
                            {
                                const vector3_t head_pos = head -> properties -> cframe.pos;
                                if (head_pos.y > y_limit)
                                {
                                    const float dist = vector3_dist_dif(head_pos, camera_pos);
                                    const vector3_t f_offset = vector3_mul_num(camera_look_vector, dist);
                                    const vector3_t f_pos = vector3_add(camera_pos, f_offset);
                                    const float delta_dist = vector3_dist_dif(f_pos, head_pos);
                                    const float node_ratio = (delta_dist/dist);
                                    if (old_dist > dist)
                                    {
                                        if (max_node_ratio > node_ratio)
                                        {
                                            cee = true;
                                            old_dist = dist;
                                            closest_enemy_head = head;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            closest_enemy_exists = cee;
            free(player_list);
            usleep(10000);
        }
    });
    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        for (;;)
        {
            if (closest_enemy_exists == true)
            {
                if (closest_enemy_head != NULL)
                {
                    const vector3_t camera_pos = camera -> cframe_1.pos;
                    const vector3_t camera_look_vector = rbx_get_cframe_look_vector(camera -> cframe_1);
                    const vector3_t head_pos = closest_enemy_head -> properties -> cframe.pos;
                    
                    const float dist = vector3_dist_dif(head_pos, camera_pos);
                    const vector3_t f_offset = vector3_mul_num(camera_look_vector, dist);
                    const vector3_t f_pos = vector3_add(camera_pos, f_offset);
                    const float delta_dist = vector3_dist_dif(f_pos, head_pos);
                    const float node_ratio = (delta_dist/dist);
                    
                    if (max_node_ratio > node_ratio)
                    {
                        new_look_vector = vector3_unit(head_pos, camera_pos);
                    }
                }
            }
            usleep(2000);
        }
    });
    
    
    for (;;)
    {
        usleep(300);
        if (closest_enemy_exists == true && aimbot_on == true)
        {
            camera -> cframe_1.r20 = -new_look_vector.x;
            camera -> cframe_1.r21 = -new_look_vector.y;
            camera -> cframe_1.r22 = -new_look_vector.z;
        }
    }

    
    
}





*/
