/*
 * 
 *  locate the kernel base address for ios using s Grob library
 *  compile after downloading the lib from: https://github.com/saelo/ios-kern-utils 
 * 
 *  compile at the same directoy that libkern.h is located ..
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_traps.h>
#include <mach/mach_types.h>
#include <mach/host_priv.h>
#include <mach/vm_map.h>

#include "libkern.h"


vm_address_t get_kernel_base()
{
    kern_return_t ret;
    task_t kernel_task;
    vm_region_submap_info_data_64_t info;
    vm_size_t size;
    mach_msg_type_number_t info_count = VM_REGION_SUBMAP_INFO_COUNT_64;
    unsigned int depth = 0;
    vm_address_t addr = 0x81200000;         // lowest possible kernel base address

    ret = task_for_pid(mach_task_self(), 0, &kernel_task);
    if (ret != KERN_SUCCESS)
        return 0;

    while (1) {
        // get next memory region
        ret = vm_region_recurse_64(kernel_task, &addr, &size, &depth, (vm_region_info_t)&info, &info_count);

        if (ret != KERN_SUCCESS)
            break;

        // the kernel maps over a GB of RAM at the address where it maps
        // itself so we use that fact to detect it's position
        if (size > 1024*1024*1024)
            return addr + IMAGE_OFFSET;

        addr += size;
    }

    return 0;
}


int main(){
	vm_address_t kb = get_kernel_base();
        if (kb==0){return 1;}
        printf("kernel base found at %08x\n", (unsigned int)kb);	
        return (int)&kb;
}

/*

clang kloc.c  -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS12.1.sdk -arch armv7 -arch armv7s -arch arm64 -o kl
root# ldid -Sa.plist kl
root# chmod a+x kl
root# ./kl
kernel base found at 90001000


*/

