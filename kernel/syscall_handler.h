/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef SYSCALL_HANDLER_H
#define SYSCALL_HANDLER_H

/* Only kernel/syscall.handlers invoked by other parts of kernel code should be declared here. */

int sys_process_run(const char* path, int argc, const char** argv);
int sys_process_exec(const char* path, int argc, const char** argv);

int sys_process_sleep(unsigned int ms);

int sys_mkdir(int fd, const char* path);
int sys_rmdir(int fd, const char* path);
int sys_chdir(const char* path);

int sys_open_window(int wd, int x, int y, int w, int h);
int sys_process_object_max();

static char* __cwd = "/";
#endif
