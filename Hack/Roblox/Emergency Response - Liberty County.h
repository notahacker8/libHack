





/*


void rbx_emergency_response_liberty_county_hack()
{
    
    
    
#pragma mark -
#pragma mark Globals
    
    
    
    
    static vm_offset_t service_count = 0;
    rbx_instance_t* game = rbx_get_game_instance();
    rbx_instance_t** services = rbx_get_children((void*)game, &service_count);
    
    rbx_instance_t* workspace = (void*)services[__RBX_WORKSPACE_SERVICE_INDEX__];
    rbx_instance_t* players = (void*)services[__RBX_PLAYERS_SERVICE_INDEX__];
    const static int max_players = 30;

    rbx_camera_t* camera = rbx_get_current_camera(workspace);
    rbx_player_t* local_player = rbx_get_local_player(players);
    rbx_instance_t* teams = services[__RBX_TEAMS_SERVICE_INDEX__];
    
    rbx_instance_t* police_team = (void*)rbx_find_first_child(teams, "Police");
    rbx_instance_t* sheriff_team = (void*)rbx_find_first_child(teams, "Sheriff");
    rbx_instance_t* civilan_team = (void*)rbx_find_first_child(teams, "Civilian");
    
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
            loop_refresh_esp_view_array(esp_box_array, 0, max_players, 10000);
            loop_refresh_esp_view_array(esp_text_array, 0, max_players, 10000);
        }
    });
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^
    {
        static vm_offset_t player_count = 0;
        for (;;)
        {
            rbx_player_t** player_list = (rbx_player_t**)rbx_get_children((void*)players, &player_count);
            
            for (vm_offset_t i = 0 ; i < player_count ; i++)
            {
                const rbx_player_t* player = player_list[i];
                
                NSColor* esp_text_color = NSColor.clearColor;
                
                if (player != NULL && player != local_player)
                {
                    const rbx_instance_t* character = player -> character;
                    const rbx_instance_t* team = player -> team;
                    
                    bzero(player_name_array[i], __RBX_MAX_PLAYER_NAME_LENGTH__);
                    strcpy(player_name_array[i], ((rbx_instance_t*)player) -> name + 1);
                    
                    if (team == civilan_team)
                    {
                        esp_text_color = NSColor.grayColor;
                    }
                    if (team == sheriff_team)
                    {
                        esp_text_color = NSColor.brownColor;
                    }
                    if (team == police_team)
                    {
                        esp_text_color = NSColor.blueColor;
                    }
                    
                    if (character != NULL)
                    {
                        const rbx_part_t* head = (void*)rbx_find_first_child(character, "Head");
                        if (head != NULL)
                        {
                            const vector3_t head_pos =  head -> properties -> cframe.pos;
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
            usleep(1500);
            free(player_list);
        }
    
    });
    
    
    
    
    
    
    
    
    
    
    
    
}








*/
