



#define __RBX_WORKSPACE_SERVICE_INDEX__ 0
#define __RBX_PLAYERS_SERVICE_INDEX__ 12
#define __RBX_STARTER_PLAYER_SERVICE_INDEX__ 22
#define __RBX_STARTER_PACK_SERVICE_INDEX__ 23
#define __RBX_STARTER_GUI_SERVICE_INDEX__ 24
#define __RBX_CORE_GUI_SERVICE_INDEX__ 25
#define __RBX_LIGHTING_SERVICE_INDEX__ 66
#define __RBX_TEAMS_SERVICE_INDEX__ 74
#define __RBX_REPLICATED_STORAGE_SERVICE_INDEX__ 75

#define __RBX_TOTAL_Y_GUI_INSET 76
#define __RBX_TOTAL_X_GUI_INSET 0

#define __RBX_MAX_PLAYER_NAME_LENGTH__ 21

#define __RBX_EMERGENCY_RESPONSE___LIBERTY_COUNTY_PLACE_ID__ 2534724415
#define __RBX_PHANTOM_FORCES_PLACE_ID__ 292439477
#define __RBX_MURDER_MYSTERY_2_PLACE_ID__ 142823291
#define __RBX_ARSENAL_PLACE_ID__ 286090429
#define __RBX_ZO_PLACE_ID__ 6678877691
#define __RBX_POLYBATTLE_PLACE_ID__ 4716045691
#define __RBX_WEAPONRY_PLACE_ID__ 3297964905


#define __RBX_METHOD_TYPE_GETTER__ 1
#define __RBX_METHOD_TYPE_SETTER__ 2
#define __RBX_METHOD_TYPE_UNIQUE__ 3

// 64 00 00 00 00 00 00 00 32 00 00 00 00 00 00 00 1E 00 00 00 00 00 00 00





/*
 
 ---- NOTES ----
 - A 'child' is defined as a POINTER to a structure, not the structure itself.
 
 
 */




#pragma mark    -
#pragma mark    Object Structs


typedef struct
{
    ///Length of the string but doubled.
    __int8_t str_length_x_2;
    char starting_byte;
}
rbx_string_t;


typedef struct
{
    float r0;           // + 0x0
    float r10;          // + 0x4
    float r20;          // + 0x8
    float r1;           // + 0xc
    float r11;          // + 0x10
    float r21;          // + 0x14
    float r2;           // + 0x18
    float r12;          // + 0x1c
    float r22;          // + 0x20
    vector3_t pos;      // + 0x24
}
rbx_cframe_t;


typedef struct
{
    void* actual_child;
    char __pad__1__[sizeof(long)];
}
rbx_child_t;


typedef struct
{
    void** first_child_ptr;     // + 0x0
    void** last_child_ptr;      // + 0x8
}
rbx_children_info_t;


typedef struct
{
    char __pad__1__[8];     // + 0x0
    char* class_name;       // + 0x8
}
rbx_class_info_t;


typedef struct
{
    char __pad__1__[0x8];                       // + 0x0
    void* instance_self;                        // + 0x8
    char __pad__2__[0x8];                       // + 0x10
    rbx_class_info_t* class_info_ptr;           // + 0x18
    char __pad__3__[0x18];                      // + 0x20
    bool archivable;                            // + 0x38
    char __pad__4__[0x7];                       // + 0x39
    char* name;                                 // + 0x40
    rbx_children_info_t* children_info_ptr;     // + 0x48
    char __pad__5__[0x8];                       // + 0x50
    void* parent;                               // + 0x58
}
rbx_instance_t;


typedef struct
{
    char __pad__1__[0x18];
    rbx_instance_t game_instance;
}
rbx_raw_game_t;


typedef struct
{
    char __pad__0x0__[0xd0];            // + 0x0
    rbx_instance_t* character;          // + 0xd0
    char __pad__0xd8__[0x48];           // + 0xd8
    rbx_instance_t* team;               // + 0x120
}
rbx_player_t;


typedef struct
{
    char __pad__1__[0x8];       // + 0x0
    void* getter;               // + 0x8
    char __pad__2__[0x8];       // + 0x10
    void* setter;               // + 0x18
}
rbx_getter_setter_methods_t;


typedef struct
{
    char __pad__1__[0x8];                       // + 0x0
    const char* property_name;                  // + 0x8
    char __pad__2__[0x28];                      // + 0x10
    rbx_class_info_t* class_info;               // + 0x38
    char __pad__3__[0x18];                      // + 0x40
    rbx_getter_setter_methods_t* methods;       // + 0x58
}
rbx_getter_setter_method_table_property_t;


typedef struct
{
    void* pointee;                                              // + 0x0
    const char* property_name;                                  // + 0x8
    char __pad__2__[0x28];                                      // + 0x10
    rbx_class_info_t* class_info;                               // + 0x38
    char __pad__3__[0x18];                                      // + 0x40
    rbx_getter_setter_methods_t* getter_setter_methods;         // + 0x58
    rbx_getter_setter_methods_t* back_up_getter_setter_methods; // + 0x60
    char __pad__4__[0x18];                                      // + 0x68
    void* unique_method;                                        // + 0x80
}
rbx_method_info_t;


typedef struct
{
    rbx_method_info_t** method_info_array;
    long method_info_array_end;
}
rbx_method_info_array_info_t;




#pragma mark    Custom Structs




typedef struct
{
    NSPoint point;
    float depth;
    float magnitude;
}
custom_rbx_world_to_screen_info_t;




#pragma mark    Function Types




typedef void rbx_r_void_p_ptr_ptr_f(void*, void*);


typedef void rbx_r_void_p_ptr_f(void*);
typedef void rbx_r_void_p_class_class_f(void*, void*);
typedef void* rbx_r_class_p_class_class_f(void*, void*);
typedef void rbx_r_void_p_class_float_f(void*, float);
typedef void rbx_r_void_p_class_int_f(void*, char);
typedef void rbx_r_void_p_class_cframe_ptr_f(void*, rbx_cframe_t*);
typedef float rbx_r_float_p_class_f(void*);
typedef rbx_cframe_t* rbx_r_cframe_ptr_p_class_f(void*);

typedef void amogus_f(int, char*);

typedef void amogus_ffff(void*, void*, void*);



typedef void rbx_set_humanoid_walkspeed_f(void*, float);
typedef float rbx_get_humanoid_walkspeed_f(void*);

typedef void rbx_set_tool_canbedropped_f(void*, bool);
typedef void rbx_tool_activate_f(void*);

typedef void rbx_set_humanoid_hipheight_f(void*, float);
typedef void rbx_set_humanoid_jumppower_f(void*, float);
typedef void rbx_set_humanoid_state_f(void*, int);
typedef void rbx_set_humanoid_sit_f(void*, bool);

typedef void rbx_set_workspace_gravity_f(void*, float);

typedef void rbx_set_camera_cframe_f(void*, rbx_cframe_t*);

typedef rbx_cframe_t* rbx_get_camera_cframe_f(void*);

typedef rbx_cframe_t* rbx_get_basepart_cframe_f(void*);
typedef void rbx_set_basepart_cframe_f(void*, rbx_cframe_t*);


typedef vector3_t* rbx_get_basepart_velocity_f(void*);

typedef void rbx_chat_chat_f(void*, char*);

typedef void* rbx_get_player_character_f(void*);

typedef void rbx_remoteevent_fireserver_f(void*, void*);




typedef union
{
    void* ptr;
    unsigned char bytes[8];
}
ptr_bytes_u;
