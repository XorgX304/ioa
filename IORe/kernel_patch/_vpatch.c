

/*

this module locates a signiture inside the kernel memory and patch it..
for this example we can change the kernel ver..
but you can change the code and it should work genariclly..
you can also look for offsets liek this w/o ida..
work your head and change the code..
root$ ls
CMakeLists 2.txt	common.c		kloc.c
CMakeLists.txt		common.h		kp
README			find.c			kp.c
_vpatch			find.h			libkern.h
_vpatch.c		ios-classify.h		machine.h
arch.h			k			mem.c
base.c			kdump.c			r1
binary.h		kl
root$ 
((see all the files your need at this directory to comiple.. 
taken from saelo's ios-kern-utils..
((navigate to /master/lib/kernel and copy the files there place your code there,
and compile..))
((change the sdk to your own one.. found under xcode..))
root$ clang _vpatch.c  -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS12.1.sdk -arch armv7 -arch armv7s -arch arm64 -o k
now at the ssh to ur phone:
root# uname -a
Darwin ga 14.0.0 Darwin Kernel Version 14.0.0: Fri Mar 28 21:15:11 PDT 2014; root:xnu-2423.10.70~1/RELEASE_ARM_S5L8950X iPhone5,3 arm N48AP Darwin
root# chmod a+x k
root# ldid -Sa.plist k
root# ./k
[*] kernel base address found at: 0x84401000
[*] found _version at 0x846da82c
[*] done, check "uname -a"
root# uname -a
Darwin ga 14.0.0 fuck you kernel; root:xnu-2423.10.70~1/RELEASE_ARM_S5L8950X iPhone5,3 arm N48AP Darwin


	change the kernel version:


From hopper dissembler:

idx name
145 sub_80002000



	_version:
802da85c:	db	"Darwin Kernel Version 14.0.0: ...
802da8c3



>>> a = 0x802da85c
>>> b = 0x80002000
>>> a - b
2984028

(And from offset just to be sure..)
2984028

dynamic approach is to find "Darwin Kernel .. "
By searching

Hex value of Darwin kernel is: 

44 61 72 77 69 6E 20 4B 65 72 6E 65 6C



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
#include <mach/mach.h>
#include <sys/sysctl.h>

#include "libkern.h"

// we have to declare this other wise the compiler would not 
// pass the arguments right ..
int vwrite(vm_address_t addr, unsigned int dt);


#define MAX_CHUNK_SIZE 0x500


#include <spawn.h>

extern char **environ;

void run_cmd(char *cmd)
{
    pid_t pid;
    char *argv[] = {"sh", "-c", cmd, NULL};
    int status;
    
    status = posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);
    if (status == 0) {
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
        }
    }
}

static void hexdump(unsigned char *data, size_t size, int offsetof)
{
    int i;
    char cs[17];
    memset(cs, 0, 17);

    for(i = offsetof; i < size; i++)
    {
        if(i != 0 && i % 0x10 == 0)
        {
            printf(" |%s|\n", cs);
            memset(cs, 0, 17);
        }
        else if(i != 0 && i % 0x8 == 0)
        {
            printf(" ");
        }
        printf("%02X ", data[i]);
        cs[(i % 0x10)] = (data[i] >= 0x20 && data[i] <= 0x7e) ? data[i] : '.';
    }

    i = i % 0x10;
    if(i != 0)
    {
        if(i <= 0x8)
        {
            printf(" ");
        }
        while(i++ < 0x10)
        {
            printf("   ");
        }
    }
    printf(" |%s|\n", cs);
}


vm_address_t get_kernel_base()
{
    kern_return_t ret;
    task_t kernel_task;
    vm_region_submap_info_data_64_t info;
    vm_size_t size;
    mach_msg_type_number_t info_count = VM_REGION_SUBMAP_INFO_COUNT_64;
    unsigned int depth = 0;
    vm_address_t addr = 0x81200000;         

    ret = task_for_pid(mach_task_self(), 0, &kernel_task);
    if (ret != KERN_SUCCESS)
        return 0;

    while (1) {

        ret = vm_region_recurse_64(kernel_task, &addr, &size, &depth, (vm_region_info_t)&info, &info_count);

        if (ret != KERN_SUCCESS)
            break;

        if (size > 1024*1024*1024)
            return addr + IMAGE_OFFSET;

        addr += size;
    }

    return 0;
}


vm_size_t read_kernel(vm_address_t addr, vm_size_t size, unsigned char* buf)
{
    kern_return_t ret;
    task_t kernel_task;
    vm_size_t remainder = size;
    vm_size_t bytes_read = 0;

    ret = task_for_pid(mach_task_self(), 0, &kernel_task);
    if (ret != KERN_SUCCESS)
        return -1;

    vm_address_t end = addr + size;

    while (addr < end) {
        size = remainder > MAX_CHUNK_SIZE ? MAX_CHUNK_SIZE : remainder;

        ret = vm_read_overwrite(kernel_task, addr, size, (vm_address_t)(buf + bytes_read), &size);
        if (ret != KERN_SUCCESS || size == 0)
            break;

        bytes_read += size;
        addr += size;
        remainder -= size;
    }

    return bytes_read;
}

vm_address_t find_bytes(vm_address_t start, vm_address_t end, unsigned char* bytes, size_t length)
{
    vm_address_t ret = 0;


	// 4000000    

	vm_address_t i = 0x100000;

	while ( i < (end - start) ){

		// printf("[*] i: 0x%08x\n", (unsigned int)i);
		// printf("[*] i: 0x%08x\n", (unsigned int)(start+i));

		
		unsigned char* buf = malloc(0x100000);


        	if (read_kernel(start + i - 0x100000, 0x100000, buf)) {

            		void* addr = memmem(buf, 0x100000, bytes, length);

            		if (addr){

				//printf("[*] start+i: 0x%08x\n", (unsigned int)(start+i));
				//printf("[*] addr: 0x%08x\n", (unsigned int)addr);
				//printf("[*] buf: 0x%08x\n", (unsigned int)buf);

				

				unsigned int a = (unsigned int)(start +i - 0x100000);
				unsigned int b = (unsigned int)addr;
				unsigned int c = (unsigned int)buf;

				unsigned int retval = a + b - c;
				
				//printf("[*] buf: 0x%08x\n", retval);
				//printf("[1] found _version at 0x%08x\n", retval);

				//printf("%d\n",(int)addr);

                                //hexdump(buf, 0x100, (int)addr);

                		ret = (vm_address_t)retval;
				
				fflush( stdout );
				sleep(3);				

				break;				

			}
        	}

        	free(buf);

		i += 0x100000;

	}

    

    return ret;


}

int vwrite(vm_address_t addr, unsigned int dt){

	// unsigned int dy = 0x41414141;
	// printf("1 0x%08x\n", (vm_address_t)dy);
        // printf("sizeof 0x%08x\n", sizeof(uint64_t));


        kern_return_t ret;
        task_t kernel_task; 
        ret = task_for_pid(mach_task_self(), 0, &kernel_task);

        // printf("1 0x%08x\n", (vm_address_t)dt);
	// printf("1 0x%08x\n", dt);
        
	// for ( int k=0;k<200000000;k++ ){}
	
	// getchar();

	fflush( stdout );
	sleep(3);
	
	kern_return_t rw = vm_write(kernel_task, addr, (vm_offset_t)&dt, sizeof(dt)); //(vm_offset_t)& (vm_address_t)&

        //	static test if there is no aslr (not true..) : 
	// kern_return_t rw = vm_write(kernel_task, (vm_address_t)0x802da85c, (int)&dt, sizeof(int)); // -> results in a kernel panic .. //(vm_address_t)&

        //printf("vm_write_ret: %08x\n", (unsigned int)rw);

        //return (int)&rw;
	return 0;
	

}



int main(){


	//uint64_t imm;
    	//void *patch = NULL;
    	//vm_size_t len = 0;
        //bool quad = false;

        //char *end;

	//imm = strtoull(argv[argc - 1], &end, 0);

	// patch = &imm;
        // len = quad ? sizeof(uint64_t) : sizeof(uint32_t);
	// int l = sizeof(patch)/sizeof(char);


	


	//for (int j = 0; j < l; j++){
		
	//	unsigned int chr = (unsigned int)patch[j];
	//	printf("[*] ch: 0x%08x\n", chr);	
	//}

	//return 0;

	

	vm_address_t kb = get_kernel_base();
	// printf("[*] kernel base address found at: 0x%08x\n", (unsigned int)kb);
	
	// getchar();

	fflush( stdout );
	sleep(3);

	// to trust offsets with the state of kernelcache availabilty is not good
        // unsigned int offset = 0x2984028;
        // vm_address_t kaddr = (vm_address_t)((unsigned int)kb + offset);
        // printf("kernel version address found at: %08x\n", (unsigned int)kaddr);
	// int re = vmwrite(kaddr);


	// So lets do it dynamicly.

	// lets just call vm_address_t find_bytes(vm_address_t start, vm_address_t end, unsigned char* bytes, size_t length)
	//					  kernel base address .. , lets do 	(kernel base address) + offset*4 cuz I guess we won't hit the end of the kernel e.g
	//										memory access violation.. but on the other hand I guess from my kernel ver
	//										and the actual kernel they won't add that many functions till _version 


	// 44 61 72 77 69 6E 20 4B 65 72 6E 65 6C

        unsigned char* lookup  = "Darwin";



	// printf("\n");
        // printf("%s\n", b);


	// 2984028 ->
	// 4000000


	vm_address_t v_addr = find_bytes(kb, kb + 0x4000000, lookup, strlen(lookup));

    	if (v_addr == 0) {
        	// printf("[!] failed to find the _version \n");
        	return -1;
    	}

    	// printf("[*] found _version at 0x%08x\n", (unsigned int)v_addr);
	
	// for ( int k=0;k<200000000;k++ ){}

	// getchar();

	//printf("[3] found _version at 0x%08x\n", v_addr);

        
	//vm_size_t wk = write_kernel(v_addr, new_kernel, strlen(new_kernel)+1);

	// vm_address_t corrected_address = (vm_address_t)&((unsigned int)v_addr-(unsigned int)0x4);
	
	char patch[] = "fuck you kernel";

	 
	int j = 0;

	// we need to write this a uint at a time, because of vm_write way of action.. 

	while ( j < sizeof(patch)){
		
		char tmp[4];
	
		int ind = 0;
		
		for ( int i = j; i < j + 4; i ++ ){

			if (i < sizeof(patch)){

				// \x20
	
				tmp[ind] = patch[i];

			}
	
			else {
			
				tmp[ind] = '\20';
			
			}
	
			ind++;

		}
	
		// printf("first four bytes: %s\n", tmp);

		char *end;
	
		char *s;
	
		//strcpy(s, tmp);

		unsigned long dest;

		memcpy(&dest, tmp, sizeof(dest));


		unsigned int taddr = (unsigned int)dest;

		// printf("converted to uint give: %08x\n", taddr);
		// printf("sizeof conversion is: %d\n", sizeof(taddr));

		// getchar();
	
		fflush( stdout );
		sleep(3);	

		unsigned int s_addr = (unsigned int)v_addr+ (unsigned int)j;
		vm_address_t d_addr = (vm_address_t)s_addr;
		
	
		int rev = vwrite(s_addr, taddr);

		

		j+=4;

	}

	

	// printf("[*] done, check \"uname -a\"\n");

	return 0;

}


