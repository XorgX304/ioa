#include <mach/mach.h>

int main(void) {
    mach_port_t kernel_task = 0;
    return task_for_pid(mach_task_self(), 0, &kernel_task);
}
