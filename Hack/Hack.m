
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <mach-o/dyld.h>
#include <mach-o/dyld_images.h>
#include <stdio.h>
#include <stdlib.h>
#include <libproc.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <mach-o/dyld_images.h>
#include <dlfcn.h>
#include <pthread.h>
#include <math.h>


#define PI 3.1415926535
#define PTR_SIZE sizeof(void*)


vm_offset_t task_read_memory(const task_t task,
                             const vm_address_t address,
                             const vm_size_t size)
{
    vm_offset_t data;
    mach_msg_type_number_t data_cnt;
    vm_read(task, address, size, &data, &data_cnt);
    return data;
}


vm_address_t base()
{
    static vm_address_t base_address = 0;
    if (base_address != 0)
    {
        return base_address;
    }
    else
    {
        base_address = (0x100000000 + _dyld_get_image_vmaddr_slide(0));
        return base_address;
    }
}


vm_offset_t __DATA_section_size()
{
    return *(long*)(base() + 0x440);
}


vm_offset_t __TEXT_section_size()
{
    return *(long*)(base() + 0x448);
}



vm_address_t hook(task_t task,
                  vm_address_t address,
                  char* code,
                  int overwrite_length,
                  int code_size)
{
    char jmp_to_hook[overwrite_length];
    const static int rel_jmp_size = 5;
    char jmp_back_hook[rel_jmp_size] = {0xe9, 0x00, 0x00, 0x00, 0x00};
    vm_protect(task, address, overwrite_length, FALSE, VM_PROT_ALL);
    
    vm_address_t hooked_code;
    int hooked_code_size = code_size + rel_jmp_size;
    
    vm_allocate(task, &hooked_code, hooked_code_size, VM_FLAGS_ANYWHERE);
    vm_write(task, hooked_code, (vm_offset_t)code, code_size);
    
    vm_offset_t jmp_to_offset = hooked_code - address - rel_jmp_size;
    vm_offset_t jmp_back_offset = (address + overwrite_length) - (hooked_code + rel_jmp_size + hooked_code_size) + rel_jmp_size;
    memset(jmp_to_hook, 0x90, overwrite_length);
    jmp_to_hook[0] = 0xe9;
    memcpy(jmp_to_hook + 1, &jmp_to_offset, rel_jmp_size - 1);
    memcpy(jmp_back_hook + 1, &jmp_back_offset, rel_jmp_size - 1);
    vm_write(task, hooked_code + hooked_code_size - rel_jmp_size, (vm_address_t)jmp_back_hook, rel_jmp_size);
    vm_protect(task, hooked_code, hooked_code_size, FALSE, VM_PROT_READ|VM_PROT_EXECUTE);
    vm_write(task, address, (vm_address_t)jmp_to_hook, (int)overwrite_length);
    
    return hooked_code;
}


vm_address_t long_hook(task_t task,
                       vm_address_t address,
                       char* code,
                       int overwrite_length,
                       int code_size)
{
    char pop_rax[1] =
    {
        0x58
    };
    char jmp_to_hook[overwrite_length];
    const static int abs_jmp_size = 14;
    char jmp_back_hook[abs_jmp_size] =
    {
        0x50,                                                               //push          rax
        0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         //movabs        rax, 0x0
        0xFF, 0xE0,                                                         //jmp           rax
        0x58                                                                //pop           rax
    };
    vm_protect(task, address, overwrite_length, FALSE, VM_PROT_ALL);
    
    vm_address_t hooked_code;
    int hooked_code_size = code_size + abs_jmp_size + 1;
    
    vm_allocate(task, &hooked_code, hooked_code_size, VM_FLAGS_ANYWHERE);
    vm_write(task, hooked_code, (vm_offset_t)pop_rax, 1);
    vm_write(task, hooked_code + 1, (vm_offset_t)code, code_size);
    
    vm_offset_t jmp_to_address = hooked_code;
    vm_offset_t jmp_back_address = address + (abs_jmp_size - 1);
    
    memset(jmp_to_hook, 0x90, overwrite_length);
    memcpy(jmp_to_hook, jmp_back_hook, abs_jmp_size);
    memcpy(jmp_to_hook + 3, &jmp_to_address, sizeof(long));
    
    memcpy(jmp_back_hook + 3, &jmp_back_address, sizeof(long));
    
    vm_write(task, address, (vm_address_t)jmp_to_hook, (int)overwrite_length);
    vm_write(task, hooked_code + (hooked_code_size - abs_jmp_size), (vm_address_t)jmp_back_hook, abs_jmp_size - 1);
    vm_protect(task, hooked_code, hooked_code_size, FALSE, VM_PROT_READ|VM_PROT_EXECUTE);
    
    return hooked_code;
}


void* copy_function(task_t task,
                    vm_address_t address,
                    int size)
{
    vm_address_t a;
    vm_allocate(task, &a, size, VM_FLAGS_ANYWHERE);
    vm_write(task, a, address, size);
    vm_protect(task, a, size, FALSE, VM_PROT_READ|VM_PROT_EXECUTE);
    return (void*)a;
}


bool is_valid_address(const task_t task,
                      void* address)
{
    bool status = false;
    vm_offset_t data;
    unsigned int dataCnt;
    const register kern_return_t kr =
    vm_read(task,
            (vm_address_t)address,
            sizeof(void*),
            &data,
            &dataCnt);
    if (kr == KERN_SUCCESS)
    {
        status = true;
    }
    return status;
}





#include "Vector3.h"
#include "ESP.h"

#include "HeadSoccer/HeadSoccer.h"
#include "HeadBasketball/HeadBasketball.h"
#include "AssaultCube/AssaultCube.h"

#include "Roblox/Structs.h"
#include "Roblox/Functions.h"
#include "Roblox/Murder Mystery 2.h"
#include "Roblox/Emergency Response - Liberty County.h"
#include "Roblox/Arsenal.h"
#include "Roblox/Weaponry.h"
#include "Roblox/Main.h"




__attribute__((constructor)) void initialize_hack()
{
    static pthread_t pthread;
    const char* progname = getprogname();
    
    if (strcmp(progname, "headsoccer") == 0)
    {
        pthread_create(&pthread, NULL, head_soccer_hack, NULL);
    }
    else if (strcmp(progname, "headbasketball") == 0)
    {
        pthread_create(&pthread, NULL, head_basketball_hack, NULL);
    }
    else if (strcmp(progname, "assaultcube") == 0)
    {
        pthread_create(&pthread, NULL, assaultcube_hack, NULL);
    }
    else if (strcmp(progname, "RobloxPlayer") == 0)
    {
        pthread_create(&pthread, NULL, rbx_poly_battle_hack, NULL);
    }
    else
    {
       
    }
}
