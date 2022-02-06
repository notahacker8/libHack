










void* roblox_hack()
{
    return NULL;
}










void rbx_jtts_hack()
{
    rbx_raw_game_t* raw_game = rbx_get_raw_game_instance();
    rbx_instance_t* game = (void*)&raw_game -> game_instance;
    
    rbx_instance_t* workspace = rbx_find_first_child_of_class(game, "Workspace");
    rbx_instance_t* players = rbx_find_first_child_of_class(game, "Players");
    rbx_player_t* local_player = rbx_get_local_player(players);
    rbx_instance_t* camera = rbx_find_first_child_of_class(workspace, "Camera");
    
    rbx_get_basepart_cframe_f* get_basepart_cframe = rbx_get_class_method_by_name("BasePart", "CFrame", __RBX_METHOD_TYPE_GETTER__);
    rbx_set_basepart_cframe_f* set_basepart_cframe = rbx_get_class_method_by_name("BasePart", "CFrame", __RBX_METHOD_TYPE_SETTER__);
    rbx_get_basepart_velocity_f* get_basepart_velocity = rbx_get_class_method_by_name("BasePart", "Velocity", __RBX_METHOD_TYPE_GETTER__);
    
    rbx_get_camera_cframe_f* get_camera_cframe = rbx_get_class_method_by_name("Camera", "CFrame", __RBX_METHOD_TYPE_GETTER__);
    rbx_set_camera_cframe_f* set_camera_cframe = rbx_get_class_method_by_name("Camera", "CFrame", __RBX_METHOD_TYPE_SETTER__);
    rbx_get_humanoid_walkspeed_f* get_camera_fieldofview = rbx_get_class_method_by_name("Camera", "FieldOfView", __RBX_METHOD_TYPE_GETTER__);
    
    
    rbx_set_humanoid_walkspeed_f* set_humanoid_walkspeed = rbx_get_class_method_by_name("Humanoid", "WalkSpeed", __RBX_METHOD_TYPE_SETTER__);
    rbx_get_humanoid_walkspeed_f* get_humanoid_walkspeed = rbx_get_class_method_by_name("Humanoid", "WalkSpeed", __RBX_METHOD_TYPE_GETTER__);
    rbx_get_humanoid_walkspeed_f* get_humanoid_health = rbx_get_class_method_by_name("Humanoid", "Health", __RBX_METHOD_TYPE_GETTER__);
    
    
    static const int max_item_count = 200;
    
    
    static NSSize window_size;
    static NSView* rbx_ogre_view;
    
    
    
#pragma mark -
#pragma mark ESP
    
    
    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^
    {
        for (;;)
        {
            dispatch_async(dispatch_get_main_queue(), ^
            {
                NSApp.windows[0].title = [NSString stringWithFormat:@"%p", workspace];
                window_size = NSApp.windows[0].contentView.frame.size;
                rbx_ogre_view = NSApp.windows[0].contentView.subviews[0];
            });
            sleep(1);
        }
    });
    
    
    
    sleep(1);
    
    void** esp_box_array = allocate_blank_esp_box_array(rbx_ogre_view, max_item_count);
    void** esp_text_array = allocate_blank_esp_text_array(rbx_ogre_view, max_item_count);
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^
    {
        for (;;)
        {
            loop_refresh_esp_view_array(esp_box_array, 0, max_item_count, 10000);
            loop_refresh_esp_view_array(esp_text_array, 0, max_item_count, 10000);
        }
    });
    

    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^
    {
        for (;;)
        {
            rbx_instance_t* item = rbx_find_first_child(workspace, "SidOrb");
            if (item != NULL)
            {
                rbx_cframe_t* item_cframe = get_basepart_cframe(item);
                vector3_t item_pos = item_cframe -> pos;
                float camera_field_of_view = get_camera_fieldofview(camera);
                rbx_cframe_t* camera_cframe = get_camera_cframe(camera);
                custom_rbx_world_to_screen_info_t wtsi = rbx_world_to_screen_point(*camera_cframe, camera_field_of_view, item_pos, window_size);
                NSPoint point = wtsi.point;
                dispatch_async(dispatch_get_main_queue(), ^
                               {
                    NSView* esp_box = (__bridge NSView*)esp_box_array[0];
                    NSTextField* esp_text = (__bridge NSTextField*)esp_text_array[0];
                    
                    if (is_valid_point(point) == true)
                    {
                        esp_box.hidden = NO;
                        esp_box.frame = NSMakeRect(point.x - 10, point.y + 30, 20, 20);
                        esp_box.layer.borderColor = NSColor.blackColor.CGColor;
                        
                        esp_text.hidden = NO;
                        esp_text.frame = NSMakeRect(point.x - 100, point.y + 60, 200, 30);
                        esp_text.textColor = NSColor.blackColor;
                        esp_text.stringValue = [NSString stringWithFormat:@"SID ORB: %f", wtsi.depth];
                    }
                    else
                    {
                        esp_text.hidden = YES;
                        esp_box.hidden = YES;
                    }
                });
                usleep(1000);
            }
        }
    
    });
 
 
     
    
}




















void rbx_poly_battle_hack()
{
    rbx_raw_game_t* raw_game = rbx_get_raw_game_instance();
    rbx_instance_t* game = (void*)&raw_game -> game_instance;
    
    rbx_instance_t* workspace = rbx_find_first_child_of_class(game, "Workspace");
    rbx_instance_t* players = rbx_find_first_child_of_class(game, "Players");
    rbx_player_t* local_player = rbx_get_local_player(players);
    rbx_instance_t* camera = rbx_find_first_child_of_class(workspace, "Camera");
    
    const int max_players = 28;
    
    rbx_get_basepart_cframe_f* get_basepart_cframe = rbx_get_class_method_by_name("BasePart", "CFrame", __RBX_METHOD_TYPE_GETTER__);
    rbx_get_basepart_velocity_f* get_basepart_velocity = rbx_get_class_method_by_name("BasePart", "Velocity", __RBX_METHOD_TYPE_GETTER__);
    
    rbx_get_camera_cframe_f* get_camera_cframe = rbx_get_class_method_by_name("Camera", "CFrame", __RBX_METHOD_TYPE_GETTER__);
    rbx_set_camera_cframe_f* set_camera_cframe = rbx_get_class_method_by_name("Camera", "CFrame", __RBX_METHOD_TYPE_SETTER__);
    rbx_get_humanoid_walkspeed_f* get_camera_fieldofview = rbx_get_class_method_by_name("Camera", "FieldOfView", __RBX_METHOD_TYPE_GETTER__);
    
    
    rbx_set_humanoid_walkspeed_f* set_humanoid_walkspeed = rbx_get_class_method_by_name("Humanoid", "WalkSpeed", __RBX_METHOD_TYPE_SETTER__);
    rbx_get_humanoid_walkspeed_f* get_humanoid_walkspeed = rbx_get_class_method_by_name("Humanoid", "WalkSpeed", __RBX_METHOD_TYPE_GETTER__);
    rbx_get_humanoid_walkspeed_f* get_humanoid_health = rbx_get_class_method_by_name("Humanoid", "Health", __RBX_METHOD_TYPE_GETTER__);
    
    
    
    static NSSize window_size;
    static NSView* rbx_ogre_view;
    
    
    static float actual_speed = 70;
    static float fake_speed = 16;
    rbx_hook_humanoid_walkspeed_setter(set_humanoid_walkspeed, &actual_speed);
    rbx_hook_humanoid_walkspeed_getter(get_humanoid_walkspeed, &fake_speed);
     
    
    
    
#pragma mark -
#pragma mark ESP
    
    
    
    
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
    
    for (register short i = 0 ; i < max_players ; i++)
    {
        player_name_array[i] = malloc(__RBX_MAX_PLAYER_NAME_LENGTH__);
    }
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^
    {
        for (;;)
        {
            loop_refresh_esp_view_array(esp_box_array, 0, max_players, 1000);
            loop_refresh_esp_view_array(esp_text_array, 0, max_players, 1000);
        }
    });
    

    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^
    {
        for (;;)
        {
            vm_offset_t player_count = 0;
            rbx_child_t* player_list = (void*)rbx_get_children(players, &player_count);
            for (vm_offset_t i = 0 ; i < player_count ; i++)
            {
                rbx_player_t* player = player_list[i].actual_child;
                
                NSColor* esp_text_color = NSColor.redColor;
                
                if (player != NULL && player != local_player)
                {
                    rbx_instance_t* player_team = player -> team;
                    rbx_instance_t* player_character = player -> character;
                    rbx_instance_t* local_player_team = local_player -> team;
                    
                    if (player_team != local_player_team || player_team == NULL)
                    {
                        bzero(player_name_array[i], __RBX_MAX_PLAYER_NAME_LENGTH__);
                        strcpy(player_name_array[i], rbx_real_str(((rbx_instance_t*)player) -> name));
                        
                        if (player_character != NULL)
                        {
                            rbx_instance_t* player_head = (void*)rbx_find_first_child(player_character, "Head");
                            rbx_instance_t* player_humanoid = (void*)rbx_find_first_child(player_character, "Humanoid");
                            
                            if (player_head != NULL && player_humanoid != NULL)
                            {
                                if (get_humanoid_health(player_humanoid) > 0)
                                {
                                    rbx_cframe_t* player_head_cframe = get_basepart_cframe(player_head);
                                    vector3_t player_head_pos = player_head_cframe -> pos;
                                    float camera_field_of_view = get_camera_fieldofview(camera);
                                    rbx_cframe_t* camera_cframe = get_camera_cframe(camera);
                                    custom_rbx_world_to_screen_info_t wtsi = rbx_world_to_screen_point(*camera_cframe, camera_field_of_view, player_head_pos, window_size);
                                    NSPoint point = wtsi.point;
                                    dispatch_async(dispatch_get_main_queue(), ^
                                                   {
                                        NSView* esp_box = (__bridge NSView*)esp_box_array[i];
                                        NSTextField* esp_text = (__bridge NSTextField*)esp_text_array[i];
                                        char* player_name = player_name_array[i];
                                        
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
            usleep(1000);
        }
    
    });
    
    
    
    static rbx_player_t* closest_enemy = NULL;
    static rbx_instance_t* closest_enemy_head = NULL;
    static rbx_instance_t* closest_enemy_humanoid = NULL;
    static rbx_instance_t* closest_enemy_hrp = NULL;
    static float dist_from_closest_enemy = 0;
    
    static bool closest_enemy_exists = false;
    static bool aimbot_on = false;
    
    static rbx_cframe_t new_camera_cframe;
    
    
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
    
    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^{
        for (;;)
        {
            long cee = false;
            float dist_to_beat = 99999;
            vm_offset_t player_list_count = 0;
            rbx_child_t* player_list = (void*)rbx_get_children(players, &player_list_count);
            for (vm_offset_t i = 0 ; i < player_list_count ; i++)
            {
                rbx_player_t* player = player_list[i].actual_child;
                if (player != local_player && player != NULL)
                {
                    rbx_instance_t* player_team = player -> team;
                    rbx_instance_t* local_player_team = local_player -> team;
                    if (player_team != local_player_team)
                    {
                        rbx_instance_t* player_character = player -> character;
                        if (player_character != NULL)
                        {
                            rbx_instance_t* player_head = rbx_find_first_child(player_character, "Head");
                            rbx_instance_t* player_humanoid = rbx_find_first_child_of_class(player_character, "Humanoid");
                            rbx_instance_t* player_hrp = rbx_find_first_child(player_character, "HumanoidRootPart");
                            if (player_head != NULL)
                            {
                                if (player_humanoid != NULL)
                                {
                                    float humanoid_healh = get_humanoid_health(player_humanoid);
                                    if (humanoid_healh > 0)
                                    {
                                        rbx_cframe_t* player_head_cframe = get_basepart_cframe(player_head);
                                        rbx_cframe_t* camera_cframe = get_camera_cframe(camera);
                                        vector3_t player_head_pos = player_head_cframe -> pos;
                                        vector3_t camera_pos = camera_cframe -> pos;
                                        vector3_t camera_look_vector = rbx_get_cframe_look_vector(*camera_cframe);
                                        
                                        float dist = vector3_dist_dif(player_head_pos, camera_pos);
                                        vector3_t delta_pos = vector3_add(camera_pos, vector3_mul_num(camera_look_vector, dist));
                                        float delta_dist = vector3_dist_dif(delta_pos, player_head_pos);
                                        float ratio = (dist/delta_dist);
                                        
                                        if (ratio > 5)
                                        {
                                            if (dist < dist_to_beat)
                                            {
                                                dist_to_beat = dist;
                                                cee = true;
                                                dist_from_closest_enemy = dist;
                                                closest_enemy = player;
                                                closest_enemy_head = player_head;
                                                closest_enemy_humanoid = player_humanoid;
                                                closest_enemy_hrp = player_hrp;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            closest_enemy_exists = cee;
            usleep(100000);
        }
    });
    
    usleep(500);
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
        for (;;)
        {
            if (closest_enemy_exists == true)
            {
                if (closest_enemy_head != NULL)
                {
                    if (closest_enemy_humanoid != NULL)
                    {
                        if (closest_enemy_hrp != NULL)
                        {
                            rbx_cframe_t* enemy_head_cframe = get_basepart_cframe(closest_enemy_head);
                            rbx_cframe_t* camera_cframe = get_camera_cframe(camera);
                            vector3_t enemy_head_pos = enemy_head_cframe -> pos;
                            vector3_t camera_pos = camera_cframe -> pos;
                            
                            vector3_t* hrp_velocity = get_basepart_velocity(closest_enemy_hrp);
                            vector3_t dif = vector3_sub(enemy_head_pos, camera_pos);
                            float dist = vector3_magnitude(dif);
                            const float div_const = 2000;
                            const float ratio = dist/div_const;
                            
                            vector3_t target_pos = vector3_add(enemy_head_pos, vector3_mul_num(*hrp_velocity, ratio));
                            target_pos.y += (2 * ratio);
                            
                            dif = vector3_sub(target_pos, camera_pos);
                            vector3_t new_camera_look_vector = vector3_div_num(dif, dist);
                            new_camera_cframe = rbx_cframe_from_pos_and_look_vector(camera_pos, new_camera_look_vector);
                        }
                    }
                }
            }
            usleep(500);
        }
    });
    
    rbx_hook_camera_cframe_setter(set_camera_cframe, &aimbot_on, &closest_enemy_exists, &new_camera_cframe);
    
}
    
    
