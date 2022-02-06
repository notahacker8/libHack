




#define rbx_real_str(str) (str + 1)



#pragma mark Instance Methods




rbx_child_t* rbx_get_children(const rbx_instance_t* instance,
                              vm_offset_t* inout_child_count)
{
    if (instance -> children_info_ptr == NULL)
    {
        *inout_child_count = 0;
        return NULL;
    }
    const rbx_children_info_t ci = *(instance -> children_info_ptr);
    vm_offset_t child_count = ((long)ci.last_child_ptr - (long)ci.first_child_ptr);
    if (child_count == 0)
    {
        *inout_child_count = 0;
        return NULL;
    }
    child_count /= (PTR_SIZE * 2);
    *inout_child_count = child_count;
    
    rbx_child_t* raw_child_array = (rbx_child_t*)ci.first_child_ptr;
    return raw_child_array;
}


vm_offset_t rbx_get_child_count(const rbx_instance_t* instance)
{
    if (instance -> children_info_ptr == NULL)
    {
        return 0;
    }
    const rbx_children_info_t ci = *(instance -> children_info_ptr);
    vm_offset_t child_count = ((long)ci.last_child_ptr - (long)ci.first_child_ptr);
    if (child_count == 0)
    {
        return 0;
    }
    child_count /= (PTR_SIZE * 2);
    return child_count;
}


rbx_instance_t* rbx_find_first_child(const rbx_instance_t* instance,
                                     const char* name)
{
    vm_offset_t child_count = 0;
    rbx_child_t* children = rbx_get_children(instance, &child_count);
    if (children == NULL)
    {
        return NULL;
    }
    for (vm_offset_t i = 0 ; i < child_count ; i++)
    {
        rbx_instance_t* test_child = children[i].actual_child;
        if (test_child != NULL)
        {
            if (strcmp(rbx_real_str((test_child -> name)), name) == 0)
            {
                return test_child;
            }
        }
    }
    return NULL;
}


rbx_instance_t* rbx_find_first_child_of_class(rbx_instance_t* instance,
                                              const char* class_name)
{
    vm_offset_t child_count = 0;
    rbx_child_t* children = rbx_get_children(instance, &child_count);
    if (children == NULL)
    {
        return NULL;
    }
    for (vm_offset_t i = 0 ; i < child_count ; i++)
    {
        rbx_instance_t* test_child = children[i].actual_child;
        if (test_child != NULL)
        {
            if (strcmp(rbx_real_str((test_child -> class_info_ptr -> class_name)), class_name) == 0)
            {
                return test_child;
            }
        }
    }
    return NULL;
}


void rbx_set_instance_name(rbx_instance_t* instance,
                           char* mem_alloc,
                           char* new_name)
{
    mem_alloc[0] = (strlen(new_name) * 2);
    strcpy(mem_alloc + 1, new_name);
    instance -> name = mem_alloc;
}



#pragma mark Extra Instance Functions



void* rbx_get_current_camera(rbx_instance_t* workspace)
{
    return (void*)(workspace -> children_info_ptr -> first_child_ptr[0]);
}


void* rbx_get_local_player(rbx_instance_t* players_service)
{
    return (void*)(players_service -> children_info_ptr -> first_child_ptr[0]);
}




#pragma mark Finder Functions




__int64_t rbx_get_place_id()
{
    static __int64_t place_id = 0;
    if (place_id != 0)
    {
        return place_id;
    }
    static const char* sign_str = "$AuthenticatedTheme";
    const unsigned long sign_len = strlen(sign_str);
    unsigned char sign[sign_len];
    memcpy(sign, sign_str, sign_len);
    vm_address_t start_loc = base() + 0x2000000;
    for (vm_offset_t i = 0 ; i < (0x1000000/8) ; i++)
    {
        const vm_address_t test_loc = start_loc + (i * 8);
        if (memcmp((void*)test_loc, sign, sign_len) == 0)
        {
            place_id = ((__int64_t*)(test_loc - 0x3b0))[0];
        }
    }
    return place_id;
}


rbx_raw_game_t* rbx_get_raw_game_instance()
{
    static rbx_raw_game_t* raw_game = NULL;
    if (raw_game != NULL)
    {
        return raw_game;
    }
    vm_address_t __DATA_sect_start = (base() + __TEXT_section_size());
    vm_address_t* search_start = (vm_address_t*)__DATA_sect_start;
    vm_offset_t count = __DATA_section_size()/sizeof(long);
    for (vm_offset_t i = 0 ; i < count ; i++)
    {
        const vm_address_t test_loc = search_start[i];
        
        ptr_bytes_u u;
        u.ptr = (void*)test_loc;
        
        if (u.bytes[0] == 0x18 && u.bytes[5] == 0x7f && u.bytes[6] == 0x00 && u.bytes[7] == 0x00)
        {
            void* possible_game = (void*)test_loc;
            if (is_valid_address(mach_task_self_, possible_game) == true)
            {
                char* name = ((rbx_instance_t*)possible_game) -> name;
                if (is_valid_address(mach_task_self_, name) == true)
                {
                    if (strcmp(rbx_real_str(name), "Game") == 0)
                    {
                        raw_game = possible_game - 0x18;
                        return raw_game;
                    }
                }
            }
        }
    }
    return raw_game;
}


void* rbx_get_global_string_table()
{
    static bool function_used = false;
    static void* string_table = NULL;
    static int encounter_count = 0;
    if (function_used == true)
    {
        return string_table;
    }
    vm_offset_t __TEXT_sect_sz = __TEXT_section_size();
    vm_offset_t __DATA_sect_sz = __DATA_section_size();
    void** search_start = (void**)(base() + __TEXT_sect_sz);
    long count = (__DATA_sect_sz/8);
    for (long i = 0 ; i < count ; i++)
    {
        char* str = rbx_real_str(search_start[i]);
        if (is_valid_address(mach_task_self_, str) == true)
        {
            if (strcmp(str, "<<<ROOT>>>") == 0)
            {
                encounter_count++;
                if (encounter_count == 2)
                {
                    string_table = search_start + i;
                    return string_table;
                }
            }
        }
    }
    function_used = true;
    return string_table;
}


vm_offset_t rbx_get_global_string_table_element_count(void** global_string_table)
{
    static bool function_used = false;
    static vm_offset_t element_count;
    static vm_offset_t counter;
    if (function_used == true)
    {
        return element_count;
    }
    for (;;)
    {
        if (global_string_table[counter] == NULL)
        {
            element_count = counter;
            return element_count;
        }
        counter++;
    }
    function_used = true;
    return element_count;
}


void* rbx_search_global_string_ref(void** global_string_table,
                                   char* real_string)
{
    void* global_string_ref = NULL;
    for (vm_offset_t i = 0 ; i < rbx_get_global_string_table_element_count(global_string_table) ; i++)
    {
        if (strcmp(real_string, rbx_real_str(global_string_table[i])) == 0)
        {
            global_string_ref = (void*)global_string_table[i];
            return global_string_ref;
        }
    }
    return global_string_ref;
}


rbx_method_info_t* rbx_search_method_info(char* class_name,
                                          char* rbx_property_name_ref)
{
    rbx_method_info_t* mi = NULL;
    vm_address_t __DATA_sect_start = (base() + __TEXT_section_size());
    void** search_start = (void**)(__DATA_sect_start);
    vm_offset_t count = __DATA_section_size()/sizeof(long);
    for (long i = 0 ; i < count ; i++)
    {
        if (search_start[i] == rbx_property_name_ref)
        {
            rbx_method_info_t* tmi = (void*)((long)search_start + ((i - 1) * 8));
            if (is_valid_address(mach_task_self_, tmi) == true)
            {
                if (is_valid_address(mach_task_self_, tmi -> pointee) == true)
                {
                    if (is_valid_address(mach_task_self_, tmi -> class_info) == true)
                    {
                        
                        ptr_bytes_u u;
                        u.ptr = (void*)tmi -> class_info -> class_name;
                        
                        if (u.bytes[5] == 0x7f && u.bytes[6] == 0x00 && u.bytes[7] == 0x00)
                        {
                            if (is_valid_address(mach_task_self_, tmi -> class_info -> class_name) == true)
                            {
                                if (strcmp(class_name, rbx_real_str(tmi -> class_info -> class_name)) == 0)
                                {
                                    mi = tmi;
                                    return mi;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return mi;
}


void* rbx_get_class_method_by_name(char* class_name,
                                   char* name,
                                   int method_type)
{
    void* method = NULL;
    void** global_string_table = rbx_get_global_string_table();
    if (global_string_table == NULL)
    {
        return NULL;
    }
    void* str_ref = rbx_search_global_string_ref(global_string_table, name);
    if (str_ref == NULL)
    {
        return NULL;
    }
    rbx_method_info_t* method_info = rbx_search_method_info(class_name, str_ref);
    if (method_info == NULL)
    {
        return NULL;
    }
    if (method_type == __RBX_METHOD_TYPE_GETTER__ || method_type == __RBX_METHOD_TYPE_SETTER__)
    {
        rbx_getter_setter_methods_t* gs_methods = method_info -> getter_setter_methods;
        
        ptr_bytes_u u;
        u.ptr = gs_methods;
        
        if (u.bytes[5] != 0x7f)
        {
            gs_methods = method_info -> back_up_getter_setter_methods;
        }
        if (method_type == __RBX_METHOD_TYPE_GETTER__)
        {
            method = gs_methods -> getter;
            return method;
        }
        if (method_type == __RBX_METHOD_TYPE_SETTER__)
        {
            method = gs_methods -> setter;
            return method;
        }
        return method;
    }
    if (method_type == __RBX_METHOD_TYPE_UNIQUE__)
    {
        method = method_info -> unique_method;
        return method;
    }
    return method;
}




#pragma mark CFrame Methods




vector3_t rbx_get_cframe_look_vector(const rbx_cframe_t cframe)
{
    return vector3_init(-cframe.r20, -cframe.r21, -cframe.r22);
}

vector3_t rbx_get_cframe_up_vector(const rbx_cframe_t cframe)
{
    return vector3_init(cframe.r10, cframe.r11, cframe.r12);
}

vector3_t rbx_get_cframe_right_vector(const rbx_cframe_t cframe)
{
    return vector3_init(cframe.r0, cframe.r1, cframe.r2);
}

rbx_cframe_t rbx_cframe_from_pos_and_look_vector(const vector3_t pos,
                                                 const vector3_t lv)
{
    rbx_cframe_t cf;
    cf.r20 = -lv.x;
    cf.r21 = -lv.y;
    cf.r22 = -lv.z;
    vector3_t rv = vector3_init(-lv.z, 0.00000000001, lv.x);
    float rv_mag = vector3_magnitude(rv);
    rv = vector3_div_num(rv, rv_mag);
    cf.r0 = rv.x;
    cf.r1 = rv.y;
    cf.r2 = rv.z;
    vector3_t uv = vector3_cross_product(lv, rv);
    cf.r10 = -uv.x;
    cf.r11 = -uv.y;
    cf.r12 = -uv.z;
    cf.pos = pos;
    return cf;
}




#pragma mark Camera Methods




float rbx_get_camera_relative_depth(const rbx_cframe_t camera_cframe,
                                    const vector3_t position,
                                    float* inout_magnitude)
{
    const vector3_t camera_pos = camera_cframe.pos;
    const vector3_t camera_look_vector = rbx_get_cframe_look_vector(camera_cframe);

    float side_a = vector3_dist_dif(camera_pos, position);
    *inout_magnitude = side_a;
    float side_b = side_a;
    const vector3_t look_vector_offset =  vector3_mul_num(camera_look_vector, side_b);
    float side_c = vector3_dist_dif(vector3_add(camera_pos, look_vector_offset), position);
    
    float angle_c = acos((side_a * side_a + side_b * side_b - side_c * side_c) / (2 * side_a * side_b)) * (180/PI);
    float angle_a = 90;
    float angle_b = 180 - (angle_a + angle_c);
    
    const float depth = side_a * sin(angle_b / (180/PI)) / sin(angle_a / (180/PI));
    return depth;
}


NSSize rbx_get_camera_plane_size(const float fov,
                                 const float depth,
                                 const NSSize window_size)
{
    const float aspect_ratio = window_size.width / window_size.height;
    
    //const angle_a = 90;
    const float angle_c = fov/2;
    const float angle_b = 180 - (angle_c + 90);

    //const float side_b = depth;
    const float side_c = depth * sin(angle_c / (180/PI)) / sin(angle_b / (180/PI));
    
    NSSize size;
    size.width = side_c * 2 * aspect_ratio;
    size.height = side_c * 2;
    
    return size;
}


custom_rbx_world_to_screen_info_t rbx_world_to_screen_point(const rbx_cframe_t camera_cframe,
                                                            const float field_of_view,
                                                            const vector3_t target_pos,
                                                            const NSSize window_size)
{
    const vector3_t camera_pos = camera_cframe.pos;
    const vector3_t camera_look_vector = rbx_get_cframe_look_vector(camera_cframe);
    const vector3_t camera_up_vector = rbx_get_cframe_up_vector(camera_cframe);
    const vector3_t camera_right_vector = rbx_get_cframe_right_vector(camera_cframe);
    float magnitude;
    custom_rbx_world_to_screen_info_t wtsi;
    
    const float depth = rbx_get_camera_relative_depth(camera_cframe, target_pos, &magnitude);
    
    //The target is behind the camera.
    if (depth < 0)
    {
        wtsi.point = NSMakePoint(0.0f/0.0f, 0.0f/0.0f);
        return wtsi;
    }
    
    NSSize plane_size = rbx_get_camera_plane_size(field_of_view, depth, window_size);
    
    const float plane_size_x = plane_size.width;
    const float plane_size_y = plane_size.height;
    
    const float right_angle_sin_deg = sin(90 / (180/PI));
    
    const vector3_t look_vector_offset = vector3_mul_num(camera_look_vector, depth);
    const vector3_t right_vector_offset = vector3_mul_num(camera_right_vector, plane_size_x / 2);
    const vector3_t up_vector_offset = vector3_mul_num(camera_up_vector, plane_size_y / 2);
    
    const vector3_t center_pos = vector3_add(camera_pos, look_vector_offset);
    
    
    const vector3_t r_side_pos = vector3_add(center_pos, right_vector_offset);
    const vector3_t l_side_pos = vector3_sub(center_pos, right_vector_offset);
    
    const vector3_t tr_corner_pos = vector3_add(r_side_pos, up_vector_offset);
    const vector3_t bl_corner_pos = vector3_sub(l_side_pos, up_vector_offset);
    
    
    //Where the magic happens.

    
    float side_a = vector3_dist_dif(bl_corner_pos, target_pos);
    float side_b = side_a;
    float side_c = vector3_dist_dif(vector3_add(bl_corner_pos, vector3_mul_num(camera_right_vector, side_a)), target_pos);
    
    float angle_c = acos((side_a * side_a + side_b * side_b - side_c * side_c) / (2 * side_a * side_b)) * (180/PI);
    float angle_b = 180 - (90 + angle_c);
    
    
    float dist_from_bottom = side_a * sin(angle_c / (180/PI)) / right_angle_sin_deg;
    float dist_from_left = side_a * sin(angle_b / (180/PI)) / right_angle_sin_deg;
    
    
    side_a = vector3_dist_dif(tr_corner_pos, target_pos);
    side_b = side_a;
    side_c = vector3_dist_dif(vector3_add(tr_corner_pos, vector3_mul_num(camera_right_vector, -side_a)), target_pos);
    
    angle_c = acos((side_a * side_a + side_b * side_b - side_c * side_c) / (2 * side_a * side_b)) * (180/PI);
    angle_b = 180 - (90 + angle_c);
    
    
    const float dist_from_top = side_a * sin(angle_c / (180/PI)) / right_angle_sin_deg;

    
    float x_dist = dist_from_left;
    float y_dist = dist_from_bottom;
    
    
    if (dist_from_top > plane_size_y)
    {
        y_dist = -y_dist;
    }
    
       
    
    const float x_ratio = x_dist / plane_size_x;
    const float x = (window_size.width * x_ratio);
        
    const float y_ratio = y_dist / plane_size_y;
    const float y = (window_size.height * y_ratio);
    
    wtsi.point.x = x;
    wtsi.point.y = y - (__RBX_TOTAL_Y_GUI_INSET/2);
    wtsi.depth = depth;
    wtsi.magnitude = magnitude;
    
    return wtsi;
}




#pragma mark Method Hooks




void rbx_hook_humanoid_walkspeed_getter(void* func,
                                        float* masked_speed_ptr)
{
    static bool hooked = false;
    if (hooked == false)
    {
        hooked = true;
        vm_address_t hook_address = (vm_address_t)func;
        
        char original_code[15];
        memcpy(original_code, func, sizeof(original_code));
        
        char added_code[] =
        {
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         //movabs        rcx, 0x0
            0x8B, 0x09                                                          //mov           ecx, [rcx]
        };
        char code[sizeof(original_code) + sizeof(added_code)];
        
        memcpy(added_code + 2, &masked_speed_ptr, 8);
        memcpy(code, original_code, sizeof(original_code));
        memcpy(code + sizeof(original_code), added_code, sizeof(added_code));
        
        long_hook(mach_task_self_, hook_address, code, 15, sizeof(code));
    }
}


void rbx_hook_humanoid_walkspeed_setter(void* func,
                                        float* speed_ptr)
{
    static bool hooked = false;
    if (hooked == false)
    {
        hooked = true;
        vm_address_t hook_address = (vm_address_t)func;
        
        char original_code[18];
        memcpy(original_code, func, sizeof(original_code));
        
        char injected_code[] =
        {
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                     //movabs        rax, 0x0
            0x8B, 0x00,                                                                     //mov           eax, [rax]
            0x66, 0x0F, 0x6E, 0xC0                                                          //movd          xmm0, eax
        };
        char code[sizeof(original_code) + sizeof(injected_code)];
        
        memcpy(injected_code + 2, &speed_ptr, 8);
        memcpy(code, injected_code, sizeof(injected_code));
        memcpy(code + sizeof(injected_code), original_code, sizeof(original_code));
        
        long_hook(mach_task_self_, hook_address, code, 18, sizeof(code));
    }
}


void rbx_hook_camera_cframe_setter(void* func,
                                   bool* aimbot_on_ptr,
                                   bool* target_exists_ptr,
                                   rbx_cframe_t* cframe_ptr)
{
    static bool hooked = false;
    if (hooked == false)
    {
        
        hooked = true;
        vm_address_t hook_address = (vm_address_t)func;
        char original_code[16];
        memcpy(original_code, func, sizeof(original_code));
        
        char injected_code[] =
        {
            0x57, 0x52, 0x51, 0x53, 0x48, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3B, 0x00, 0x74, 0x2B, 0x48, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3B, 0x00, 0x74, 0x1C, 0x8B, 0x7E, 0x24, 0x8B, 0x56, 0x28, 0x8B, 0x4E, 0x2C, 0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x89, 0x7E, 0x24, 0x89, 0x56, 0x28, 0x89, 0x4E, 0x2C, 0x5B, 0x59, 0x5A, 0x5F
        };
        
        
        char code[sizeof(original_code) + sizeof(injected_code)];
        
        memcpy(injected_code + 6, &aimbot_on_ptr, sizeof(long));
        memcpy(injected_code + 0x13 + 2, &target_exists_ptr, sizeof(long));
        memcpy(injected_code + 0x2b + 2, &cframe_ptr, sizeof(long));
        
        memcpy(code, injected_code, sizeof(injected_code));
        memcpy(code + sizeof(injected_code), original_code, sizeof(original_code));
        
        long_hook(mach_task_self_, hook_address, code, 16, sizeof(code));
        
    }
}





































































































































































































































#pragma mark PolyBattle






/*




void rbx_polybattle_hack()
{
    
    
    
#pragma mark -
#pragma mark Globals
    
    
    
    
    static vm_offset_t service_count = 0;
    
    rbx_humanoid_class_methods_t* humanoid_class_methods = rbx_get_humanoid_class_methods();
    rbx_camera_class_methods_t* camera_class_methods = (rbx_camera_class_methods_t*)(base() + 0xa6ceec);
    
    rbx_r_float_p_class_f* rbx_get_humanoid_health = NULL; //(rbx_r_float_p_class_f*)(humanoid_class_methods -> health_setter);
    rbx_r_void_p_class_cframe_ptr_f* rbx_set_camera_cframe = (rbx_r_void_p_class_cframe_ptr_f*)(camera_class_methods -> cframe_setter);
    
    rbx_instance_t* game = rbx_get_game_instance();
    rbx_instance_t** services = rbx_get_children((void*)game, &service_count);
    
    rbx_instance_t* workspace = (void*)services[__RBX_WORKSPACE_SERVICE_INDEX__];
    rbx_instance_t* players = (void*)services[__RBX_PLAYERS_SERVICE_INDEX__];
    
    rbx_camera_t* camera = rbx_get_current_camera(workspace);
    rbx_player_t* local_player = rbx_get_local_player(players);
    
    const static float max_node_ratio = 0.1;
    
    static bool closest_enemy_exists = false;
    static bool aimbot_on = false;
    
    static rbx_part_t* closest_enemy_head;
    static rbx_part_t* closest_enemy_hrp;
    static rbx_instance_t* closest_enemy_hum;
    static vector3_t new_look_vector;
    
    
    
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
    
    
    
    
    
#pragma mark -
#pragma mark Aimbot
    
    
    
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^{
        for (;;)
        {
            bool cee = false;
            float old_dist = 999999;
            static vm_offset_t player_count = 0;
            rbx_player_t** player_list = (rbx_player_t**)rbx_get_children((void*)players, &player_count);
            for (vm_offset_t i = 0 ; i < player_count ; i++)
            {
                const vector3_t camera_pos = camera -> cframe_1.pos;
                const rbx_player_t* player = player_list[i];
                
                if (player != NULL && player != local_player)
                {
                    if (player -> team != local_player -> team || local_player -> team == NULL)
                    {
                        const rbx_instance_t* character = player -> character;
                        if (character != NULL)
                        {
                            rbx_instance_t* hum = (void*)rbx_find_first_child_of_class((void*)character, "Humanoid");
                            rbx_part_t* head = (void*)rbx_find_first_child(character, "Head");
                            rbx_part_t* hrp = (void*)rbx_find_first_child(character, "HumanoidRootPart");
                            if (head != NULL && hrp != NULL && hum != NULL)
                            {
                                const vector3_t head_pos = head -> properties -> cframe.pos;
                                const vector3_t camera_look_vector = rbx_get_cframe_look_vector(camera -> cframe_1);
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
                                        closest_enemy_hrp = hrp;
                                        closest_enemy_hum = hum;
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
                if (closest_enemy_head != NULL && closest_enemy_hrp != NULL && closest_enemy_hum != NULL)
                {
                    const vector3_t camera_pos = camera -> cframe_1.pos;
                    const vector3_t head_pos = closest_enemy_head -> properties -> cframe.pos;
                    const vector3_t hrp_vel = closest_enemy_hrp -> properties -> velocity;
                    
                    const float dist = vector3_dist_dif(head_pos, camera_pos);
                    const float ratio = dist/1000;
                    vector3_t target_pos = vector3_add(head_pos, vector3_mul_num(hrp_vel, ratio));
                    new_look_vector = vector3_unit(target_pos, camera_pos);
                }
            }
            usleep(1000);
        }
    });
    
    
    for (;;)
    {
        usleep(300);
        if (closest_enemy_exists == true && aimbot_on == true)
        {
            rbx_cframe_t cf = rbx_cframe_from_pos_and_look_vector(camera -> cframe_1.pos, new_look_vector);
            rbx_set_camera_cframe(camera, &cf);
        }
    }

    
    
}
*/
