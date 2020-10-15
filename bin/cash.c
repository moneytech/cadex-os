/**
 * Copyright (C) 2019-2020 OpenCreeck
 * This software is distributed under the GNU General Public License
 * See the file LICENSE for details
 */

/**
 * A shell interpreter designed for simplicity; CaSh means Cadex Shell
 */
#include <bits/cwd.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define CASH_BUILD      "beta"
#define CASH_VERSION    "1.0.17"

int tmp1 = 0;
// Basic implementation of sudo
extern int getAuth() {
    char *passwd[1024];

password:
    printf("sudo: password for root: ");
    scanf(passwd, sizeof(passwd));
    if (!strcmp(passwd, "root")) {
        return 0;
    } else {
        printf("Wrong password\n");
        if (tmp1 > 2) {
            printf("Max tries exceeded\n");
            return 1;
        }
        tmp1 += 1;
        goto password;
    }
}

void print_directory(char *d, int length) {
    while (length > 0) {
        printf("%s\n", d);
        int len = strlen(d) + 1;
        d += len;
        length -= len;
    }
}

int do_command(char *line) {
    const char *pch = strtok(line, " ");
    if (pch && !strcmp(pch, "echo")) {
        pch = strtok(0, " ");
        if (pch)
            printf("%s\n", pch);
    } else if (pch && !strcmp(pch, "start")) {
        pch = strtok(0, " ");
        if (pch) {
            const char *argv[20];
            argv[0] = pch;
            int i = 1;
            char *next;
            while ((next = strtok(0, " "))) {
                argv[i++] = next;
            }
            int pid = fork();
            if (pid != 0) {
                printf("started process %d\n", pid);
            } else {
                exec(pch, 2, argv);
            }
        } else
            printf("cash: start: missing argument\n");
    } else if (pch && !strcmp(pch, "run")) {
        pch = strtok(0, " ");
        if (pch) {
            const char *argv[20];
            argv[0] = pch;
            int i = 1;
            char *next;
            while ((next = strtok(0, " "))) {
                argv[i++] = next;
            }
            int pid = proc_run(argv[0], i, &argv[0]);
            if (pid > 1) {
                printf("cash: started process %d\n", pid);
                syscall_process_yield();
                struct process_info info;
                syscall_process_wait(&info, -1);
                printf("cash: process %d exited with status %d\n", info.pid,
                       info.exitcode);
                syscall_process_reap(info.pid);
            } else {
                printf("cash: could not run '%s': %s\n", argv[0],
                       strerror(pid));
            }
        } else {
            printf("cash: run: requires argument\n");
        }
    } else if (pch && !strcmp(pch, "reap")) {
        pch = strtok(0, " ");
        int pid;
        if (pch && str2int(pch, &pid)) {
            if (syscall_process_reap(pid)) {
                printf("reap failed!\n");
            } else {
                printf("processed reaped!\n");
            }
        } else
            printf("reap: expected process id number but got %s\n", pch);
    } else if (pch && !strcmp(pch, "kill")) {
        pch = strtok(0, " ");
        int pid;
        if (pch && str2int(pch, &pid)) {
            _process_kill(pid);
        } else
            printf("kill: expected process id number but got %s\n", pch);
    } else if (pch && !strcmp(pch, "wait")) {
        pch = strtok(0, " ");
        if (pch)
            printf("%s: unexpected argument\n", pch);
        else {
            struct process_info info;
            if (syscall_process_wait(&info, 5000) > 0) {
                printf("process %d exited with status %d\n", info.pid,
                       info.exitcode);
            } else {
                printf("wait: timeout\n");
            }
        }
    } else if (pch && !strcmp(pch, "ls")) {
        char buffer[1024];
        int fd = syscall_open_file("/", 0, 0);
        if (fd >= 0) {
            int length = syscall_object_list(fd, buffer, 1024);
            syscall_object_close(fd);
            print_directory(buffer, length);
        }
    } else if (pch && !strcmp(pch, "cd")) {
        char *path = strtok(0, " ");
        if (!path) {
            printf("usage: cd <path>\n");
            return 1;
        }
        syscall_chdir(path);
    } else if (pch && !strcmp(pch, "help")) {
        printf("Cadex Shell (CaSh) version %s-%s (x86-pc-cadex)\nThese shell "
               "commands are defined internally (inbuilt). Type 'help' to see "
               "this list \n - echo <text>\n - run <path>\n - mount <unit_no> "
               "<fs_type>\n - ls <path>\n - cd <path>\n - start <path>\n - "
               "kill <pid>\n - reap <pid>\n - wait\n - help\n - exit\n",
               CASH_VERSION, CASH_BUILD);
    } else if (pch && !strcmp(pch, "exit")) {
        _process_exit(0);
        return 0;
    } else if (pch && !strcmp(pch, "sudo")) {
        if (getAuth() == 0) {
            printf("-cash: got root permission\n");
        } else {
            printf("-cash: error: getting root permission failed!\n");
        }
    } else if (pch) {
        printf("-cash: %s: command/program not found\n", pch);
    }
    return 0;
}

int readline(char *line, int length) {
    int i = 0;
    char c;
    while (1) {
        read_object(0, &c, 1);
        if (c == ASCII_CR) {
            printf_putchar(c);
            line[i] = 0;
            return i;
        } else if (c == ASCII_BS) {
            if (i > 0) {
                i--;
                printf_putchar(c);
            }
        } else {
            if (i < (length - 1)) {
                line[i] = c;
                i++;
                printf_putchar(c);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char line[MAX_LINE_LENGTH];

    while (1) {
        printf("cash-1.2# ");
        if (scanf(line, sizeof(line))) {
            do_command(line);
        }
    }
}
