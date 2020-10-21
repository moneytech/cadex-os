/**
 * Copyright (C) 2019-2020 The CadexOS Project
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

#ifndef LIBRARY_UNISTD_H
#define LIBRARY_UNISTD_H
#pragma once

#include <library/_cheader.h>
#include <library/ascii.h>
#include <library/const.h>
#include <library/ctype.h>
#include <library/errno.h>
#include <library/float.h>
#include <library/malloc.h>
#include <library/math.h>
#include <library/objno.h>
#include <library/stdbool.h>
#include <library/stddef.h>
#include <library/stdint.h>
#include <library/stdio.h>
#include <library/stdlib.h>
#include <library/strtoui.h>
#include <library/syscalls.h>
#include <library/types.h>
#include <sys/environ.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int getpid(void);
extern int getppid(void);

extern int open(const char *filename, int mode);
extern int close(int fd);

extern int fork(void);

extern int execl(const char *path, const char *arg, ...);
extern int execlp(const char *file, const char *arg, ...);
extern int execle(const char *path, const char *arg, ...);
extern int execv(const char *path, char *const argv[]);
extern int execvp(const char *file, char *const argv[]);
extern int execvpe(const char *file, char *const argv[], char *const envp[]);
extern int execve(const char *name, char *const argv[], char *const envp[]);
extern void _exit(int status);

extern int setuid(int uid);

extern int getuid(void);
extern int geteuid(void);
extern int getgid(void);
extern int getegid(void);
extern char *getcwd(char *buf, size_t size);
extern int pipe(int pipefd[2]);
extern int dup(int oldfd);
extern int dup2(int oldfd, int newfd);

extern int tcgetpgrp(int fd);
extern int tcsetpgrp(int fd, int pgrp);

extern int write(int fd, const void *buf, size_t count);
extern int read(int fd, void *buf, size_t count);

extern int symlink(const char *target, const char *linkpath);
extern int readlink(const char *pathname, char *buf, size_t bufsiz);

extern int chdir(const char *path);
// extern int fchdir(int fd);
extern int isatty(int fd);

extern unsigned int sleep(unsigned int seconds);
extern int usleep(int usec);
extern int lseek(int fd, int offset, int whence);

extern int access(const char *pathname, int mode);

extern int getopt(int argc, char *const argv[], const char *optstring);

extern char *optarg;
extern int optind, opterr, optopt;

extern int unlink(const char *pathname);

/* Unimplemented stubs */
struct utimbuf {
    int actime;
    int modtime;
};
extern char *ttyname(int fd);
extern int utime(const char *filename, const struct utimbuf *times);
extern int rmdir(const char *pathname); /* TODO  rm probably just works */
extern int chown(const char *pathname, int owner, int group);
extern char *getlogin(void);

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define F_OK 0
#define R_OK 4
#define W_OK 2
#define X_OK 1

#define ERR_FAIL    1
#define ERR_FATAL   2
#define ERR_SERIOUS 3

extern int gethostname(char *name, size_t len);
extern int sethostname(const char *name, size_t len);

extern int setsid(void);
extern int setpgid(pid_t, pid_t);
extern int getpgid(pid_t);

extern unsigned int alarm(unsigned int seconds);

extern void *sbrk(intptr_t increment);
#ifdef __cplusplus
}
#endif
#endif
