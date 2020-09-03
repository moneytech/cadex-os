#ifndef SECURITY_H
#define SECURITY_H

#include <stdio.h>
#include <library/scanf.h>

typedef struct sec_object{
    int proc_uid;
    int call_obj_id;
    char *proc_exe_name;
} sec_object_t;
int get_proc_uid();
int get_sudo_permission();

#endif // !SECURITY_H