#include "service.h"

int service_start(char* path, int argc, char* argv[], char* s_name)
{
    kprintf("        Starting %s...\n", s_name);
    int pid = sys_process_run(path, argc, &argv);
    process_yield();
    struct process_info info;
    process_wait_child(pid, &info, -1);
    if (info.exitcode > 0) {
        w_fail_status("Failed to start service ");
        kprintf("%s\n", s_name);
    } else {
        w_ok_status("Started ");
        kprintf("%s\n", s_name);
    }
    process_reap(pid);
    return 0;
}

