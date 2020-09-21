/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "kernel/types.h"
#include "kernel/stats.h"

#define DECL_SYSCALL0(fn) int syscall_##fn()
#define DECL_SYSCALL1(fn, p1) int syscall_##fn(p1)
#define DECL_SYSCALL2(fn, p1, p2) int syscall_##fn(p1, p2)
#define DECL_SYSCALL3(fn, p1, p2, p3) int syscall_##fn(p1, p2, p3)
#define DECL_SYSCALL4(fn, p1, p2, p3, p4) int syscall_##fn(p1, p2, p3, p4)
#define DECL_SYSCALL5(fn, p1, p2, p3, p4, p5) int syscall_##fn(p1, p2, p3, p4, p5)

#define DEFN_SYSCALL0(fn, num)            \
    int syscall_##fn()                    \
    {                                     \
        int a;                            \
        __asm__ __volatile__("int $0x48"  \
                             : "=a"(a)    \
                             : "0"(num)); \
        return a;                         \
    }

#define DEFN_SYSCALL1(fn, num, P1)                                             \
    int syscall_##fn(P1 p1)                                                    \
    {                                                                          \
        int __res;                                                             \
        __asm__ __volatile__("push %%ebx; movl %2,%%ebx; int $0x48; pop %%ebx" \
                             : "=a"(__res)                                     \
                             : "0"(num), "r"((int)(p1)));                      \
        return __res;                                                          \
    }

#define DEFN_SYSCALL2(fn, num, P1, P2)                                         \
    int syscall_##fn(P1 p1, P2 p2)                                             \
    {                                                                          \
        int __res;                                                             \
        __asm__ __volatile__("push %%ebx; movl %2,%%ebx; int $0x48; pop %%ebx" \
                             : "=a"(__res)                                     \
                             : "0"(num), "r"((int)(p1)), "c"((int)(p2)));      \
        return __res;                                                          \
    }

#define DEFN_SYSCALL3(fn, num, P1, P2, P3)                                                \
    int syscall_##fn(P1 p1, P2 p2, P3 p3)                                                 \
    {                                                                                     \
        int __res;                                                                        \
        __asm__ __volatile__("push %%ebx; movl %2,%%ebx; int $0x48; pop %%ebx"            \
                             : "=a"(__res)                                                \
                             : "0"(num), "r"((int)(p1)), "c"((int)(p2)), "d"((int)(p3))); \
        return __res;                                                                     \
    }

#define DEFN_SYSCALL4(fn, num, P1, P2, P3, P4)                                                            \
    int syscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4)                                                          \
    {                                                                                                     \
        int __res;                                                                                        \
        __asm__ __volatile__("push %%ebx; movl %2,%%ebx; int $0x48; pop %%ebx"                            \
                             : "=a"(__res)                                                                \
                             : "0"(num), "r"((int)(p1)), "c"((int)(p2)), "d"((int)(p3)), "S"((int)(p4))); \
        return __res;                                                                                     \
    }

#define DEFN_SYSCALL5(fn, num, P1, P2, P3, P4, P5)                                                                        \
    int syscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)                                                                   \
    {                                                                                                                     \
        int __res;                                                                                                        \
        __asm__ __volatile__("push %%ebx; movl %2,%%ebx; int $48; pop %%ebx"                                              \
                             : "=a"(__res)                                                                                \
                             : "0"(num), "r"((int)(p1)), "c"((int)(p2)), "d"((int)(p3)), "S"((int)(p4)), "D"((int)(p5))); \
        return __res;                                                                                                     \
    }

void syscall_debug(const char *str);

/* Syscalls that manipulate this process and its children. */

void _process_exit(int status);
int syscall_process_yield();
int proc_run(const char *cmd, int argc, const char **argv);
int syscall_process_wrun(const char *cmd, int argc, const char **argv, int *fds, int fd_len);
int syscall_process_fork();
void exec(const char *path, int argc, const char **argv);
int syscall_process_self();
int syscall_process_parent();
int _process_kill(unsigned int pid);
int syscall_process_reap(unsigned int pid);
int syscall_process_wait(struct process_info *info, int timeout);
int sleepThread(unsigned int ms);
int syscall_process_stats(struct process_stats *s, unsigned int pid);
extern void *syscall_process_heap(int a);

/* Syscalls that manupulates the GUI Console state */
int gui_set_bgcolor(int r, int g, int b, int a);

/* Syscalls that open or create new kernel objects for this process. */

int syscall_open_file(const char *path, int mode, kernel_flags_t flags);
int syscall_open_file_relative(int fd, const char *path, int mode, kernel_flags_t flags);
int syscall_open_dir(int fd, const char *name, kernel_flags_t flags);
int syscall_open_window(int fd, int x, int y, int w, int h);
int syscall_open_console(int fd);
int syscall_open_pipe();

/* Syscalls that manipulate kernel objects for this process. */

int syscall_object_type(int fd);
int syscall_object_dup(int fd1, int fd2);
int read_object(int fd, void *data, int length);
int read_object_nonblock(int fd, void *data, int length);
int syscall_object_list(int fd, char *buffer, int buffer_len);
int syscall_object_write(int fd, void *data, int length);
int syscall_object_seek(int fd, int offset, int whence);
int syscall_object_size(int fd, int *dims, int n);
int syscall_object_copy(int src, int dst);
int syscall_object_remove(int fd, const char *name);
int syscall_object_close(int fd);
int syscall_object_set_tag(int fd, char *tag);
int syscall_object_get_tag(int fd, char *buffer, int buffer_size);
int syscall_object_set_blocking(int fd, int b);
int syscall_object_max();

/* Syscalls that query or affect the whole system state. */

int syscall_system_stats(struct system_stats *s);
int syscall_bcache_stats(struct bcache_stats *s);

int syscall_bcache_flush();

int syscall_system_time(uint32_t *t);
int syscall_system_rtc(struct rtc_time *t);

int syscall_device_driver_stats(char *name, void *stats);

/*
These system calls are carryovers from Unix-like thinking
and need to be reworked to fit the kernel object model.
*/

int syscall_chdir(const char *path);

#endif
