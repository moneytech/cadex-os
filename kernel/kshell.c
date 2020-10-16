/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "kshell.h"
#include "acpi.h"
#include "adlib.h"
#include "bcache.h"
#include "clock.h"
#include "console.h"
#include "font.h"
#include "fs.h"
#include "fs_internal.h"
#include "graphics.h"
#include "interrupt.h"
#include "kernel/ascii.h"
#include "kernel/error.h"
#include "kernel/gfxstream.h"
#include "kernel/stats.h"
#include "kernel/syscall.h"
#include "kernel/sysinfo.h"
#include "kernel/types.h"
#include "kernelcore.h"
#include "keyboard.h"
#include "kmalloc.h"
#include "kprintf.h"
#include "library/stdio.h"
#include "library/string.h"
#include "library/syscalls.h"
#include "main.h"
#include "module.h"
#include "page.h"
#include "process.h"
#include "rtc.h"
#include "scanf.h"
#include "serial.h"
#include "string.h"
#include "syscall_handler.h"
#include "utils.h"
#include <bits/cwd.h>
#include <library/version.h>

#define BASEPORT 0x0060 /* lp1 */
#define COM1     0x3f8  /* COM1 Port Address */

// #define SHOW_DEBUG_INFO
uint16_t cursor_pos = 0, cursor_next_line_index = 1;
static uint32_t next_line_index = 1;
char *shakespeare[] = {
    "[Horatio] Now cracke a Noble heart:",
    "Goodnight sweet Prince,",
    "And flights of Angels sing thee to thy rest,",
    "Why do's the Drumme come hither?",
    "Enter Fortinbras and English Ambassador, with Drumme,",
    "Colours, and Attendants.",
    "[Fortinbras] Where is this sight?",
    "[Horatio] What is it ye would see;",
    "If ought of woe, or wonder, cease your search.",
    "[Fortinbras] His quarry cries on hauocke. Oh proud death,",
    "What feast is toward in thine eternall Cell.",
    "That thou so many Princes, at a shoote,",
    "So bloodily hast strooke.",
    "[Ambassador] The sight is dismall,",
    "And our affaires from England come too late,",
    "The eares are senselesse that should giue vs hearing,",
    "To tell him his command'ment is fulfill'd,",
    "That Rosincrance and Guildensterne are dead:",
    "Where should we haue our thankes?",
    "[Horatio] Not from his mouth,",
    "Had it th'abilitie of life to thanke you:",
    "He neuer gaue command'ment for their death.",
    "But since so iumpe vpon this bloodie question,",
    "You from the Polake warres, and you from England",
    "Are heere arriued. Giue order that these bodies",
    "High on a stage be placed to the view,",
    "And let me speake to th'yet vnknowing world,",
    "How these things came about. So shall you heare",
    "Of carnall, bloudie, and vnnaturall acts,",
    "Of accidentall iudgements, casuall slaughters",
    "Of death's put on by cunning, and forc'd cause,",
    "And in this vpshot, purposes mistooke,",
    "Falne on the Inuentors heads. All this can I",
    "Truly deliuer.",
    "[Fortinbras] Let vs hast to heare it,",
    "And call the Noblest to the Audience.",
    "For me, with sorrow, I embrace my Fortune,",
    "I haue some Rites of memory in this Kingdome,",
    "Which are ro claime, my vantage doth",
    "Inuite me,",
    "[Horatio] Of that I shall haue alwayes cause to speake,",
    "And from his mouth",
    "Whose voyce will draw on more:",
    "But let this same be presently perform'd,",
    "Euen whiles mens mindes are wilde,",
    "Lest more mischance",
    "On plots, and errors happen.",
    "[Fortinbras] Let foure Captaines",
    "Beare Hamlet like a Soldier to the Stage,",
    "For he was likely, had he beene put on",
    "To haue prou'd most royally:",
    "And for his passage,",
    "The Souldiours Musicke, and the rites of Warre",
    "Speake lowdly for him.",
    "Take vp the body; Such a sight as this",
    "Becomes the Field, but heere shewes much amis.",
    "Go, bid the Souldiers shoote.",
    "Exeunt Marching: after the which, a Peale of",
    "Ordenance are shot off.",
};

char *promptsym[] = {
    "#",
    "$",
    "%",
};

char *comd = "null";
char *excpath = "";
char *curdir = "";

int prompt = 0;
int last_run_proc_exitcode = 0;
int last_process_run = 0;

#define SHELL_HISTORY_ENTRIES 128

char *kshell_history[SHELL_HISTORY_ENTRIES];
size_t kshell_history_count = 0;
size_t kshell_history_offset = 0;

kshell_t *default_shell;

void reboot_system() {
    uint8_t temp;

    asm volatile("cli"); /* disable all interrupts */

    /* Clear all keyboard buffers (output and command buffers) */
    do {
        temp = inb(KBRD_INTRFC); /* empty user data */
        if (check_flag(temp, KBRD_BIT_KDATA) != 0)
            inb(KBRD_IO); /* empty keyboard data */
    } while (check_flag(temp, KBRD_BIT_UDATA) != 0);

    outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */

    reboot(); /* if that didn't work, reboot using the function in kernelcore.S
                 (Triple fault method) */
}

int kshell_readline(char *line, int length, int text_visible);
void print_array(char arr[], int start, int len) {
    /* Recursion base condition */
    if (start >= len)
        return;

    /* Prints the current array element */
    kprintf("%s, ", arr[start]);

    /* Recursively call print_array to print next element in array */
    print_array(arr, start - 1, len);
}

void kshell_history_insert(char *str) {
    if (kshell_history_count == SHELL_HISTORY_ENTRIES) {
        kfree(kshell_history[kshell_history_offset]);
        kshell_history[kshell_history_offset] = str;
        kshell_history_offset =
            (kshell_history_offset + 1) % SHELL_HISTORY_ENTRIES;
    } else {
        kshell_history[kshell_history_count] = str;
        kshell_history_count++;
    }
}

char *kshell_history_get(size_t item) {
    return kshell_history[(item + kshell_history_offset) %
                          SHELL_HISTORY_ENTRIES];
}

char *kshell_history_prev(size_t item) {
    return kshell_history_get(kshell_history_count - item);
}
void KPANIC(char *str) { kprintf("[PANIC]: %s\n", str); }

void kshell_show_login_prompt() {
    char *login, *password;
    struct rtc_time time;
    rtc_read(&time);
    kprintf("\n\nCadexOS livecd %s-%s %d-%d-%d %d:%d:%d %s\n", _LTS_REL_,
            __VER_SUFFIX, time.year, time.month, time.day, time.hour,
            time.minute, time.second, _K_ARCH);
login:
    kprintf("\nlivecd login: ");
    kshell_readline(login, 1024, 1);
    kprintf("password: ");
    kshell_readline(password, 1024, 0);
    if (!strcmp(login, "root")) {
        // Set fgcolor to light magenta
        graphics_set_fgcolor(196, 0, 196, 0);
        kprintf("\nWelcome to CadexOS!\n\n");
        // Set fgcolor to white
        graphics_set_fgcolor(255, 255, 255, 0);
        kprintf("https://github.com/CadexOS/Cadex-OS-Official\n\n");
    } else {
        // Fail
        kprintf("Login failed. Try again\n");
        goto login;
    }
}

int kshell_mount(const char *devname, int unit, const char *fs_type) {
    struct device *dev = device_open(devname, unit);
    if (dev) {
        struct fs *fs = fs_lookup(fs_type);
        if (fs) {
            struct fs_volume *v = fs_volume_open(fs, dev);
            if (v) {
                struct fs_dirent *d = fs_volume_root(v);
                if (d) {
                    if (current->root_dir)
                        fs_dirent_close(current->root_dir);
                    current->root_dir = d;
                    current->current_dir = fs_dirent_addref(d);
                    return 0;
                } else {
                    kprintf("mount: couldn't find root dir on %s unit %d!\n",
                            device_name(dev), device_unit(dev));
                    return -1;
                }
                fs_volume_close(v);
            } else {
                kprintf("mount: couldn't mount %s on %s unit %d\n", fs_type,
                        device_name(dev), device_unit(dev));
                return -1;
            }
        } else {
            kprintf("mount: invalid fs type: %s\n", fs_type);
            return -1;
        }
        device_close(dev);
    } else {
        kprintf("mount: couldn't open device %s unit %d\n", devname, unit);
        return -1;
    }

    return -1;
}
static int kshell_mount_nomsg(const char *devname, int unit,
                              const char *fs_type) {
    struct device *dev = device_open(devname, unit);
    if (dev) {
        struct fs *fs = fs_lookup(fs_type);
        if (fs) {
            struct fs_volume *v = fs_volume_open(fs, dev);
            if (v) {
                struct fs_dirent *d = fs_volume_root(v);
                if (d) {
                    if (current->root_dir)
                        fs_dirent_close(current->root_dir);
                    current->root_dir = d;
                    current->current_dir = fs_dirent_addref(d);
                    return 0;
                } else {
                    return -1;
                }
                fs_volume_close(v);
            } else {
                return -1;
            }
        } else {
            return -1;
        }
        device_close(dev);
    } else {
        kprintf("mount: couldn't open device %s unit %d\n", devname, unit);
        return -1;
    }

    return -1;
}

/*
Install Cadex OS and the softwares from the cdrom volume unit src
to the disk volume dst by performing a recursive copy.
TODO: This needs better error checking.
*/

int kshell_install(int src, int dst) {
    struct fs *srcfs = fs_lookup("cdfs");
    struct fs *dstfs = fs_lookup("dfs");

    if (!srcfs || !dstfs)
        return KERROR_NOT_FOUND;

    struct device *srcdev = device_open("atapi", src);
    struct device *dstdev = device_open("ata", dst);

    if (!srcdev || !dstdev)
        return KERROR_NOT_FOUND;

    struct fs_volume *srcvolume = fs_volume_open(srcfs, srcdev);
    struct fs_volume *dstvolume = fs_volume_open(dstfs, dstdev);

    if (!srcvolume || !dstvolume)
        return KERROR_NOT_FOUND;

    struct fs_dirent *srcroot = fs_volume_root(srcvolume);
    struct fs_dirent *dstroot = fs_volume_root(dstvolume);

    kprintf("installing to disk (copying from atapi unit %d and "
            "copying to ata unit %d)...\n",
            src, dst);
    dbg_printf("[kshell] copying atapi unit %d contents to ata unit %d...\n",
               src, dst);
    fs_dirent_copy(srcroot, dstroot, 0);

    fs_dirent_close(dstroot);
    fs_dirent_close(srcroot);

    fs_volume_close(srcvolume);
    fs_volume_close(dstvolume);

    device_close(srcdev);

    bcache_flush_device(dstdev);
    device_close(dstdev);

    return 0;
}

static int kshell_printdir(const char *d, int length) {
    int k = 0;
    while (length > 0) {
        struct graphics_color c;
        if (!strcmp(d, ".") || !strcmp(d, "..")) {
            kprintf("%s\n", d);
        }
        // Highlighting executable files has a bug
        else if (strew(d, ".exe")) {
            c.r = 130;
            c.g = 244;
            c.b = 130;
            c.a = 0;
            graphics_fgcolor(&graphics_root, c);
            kprintf("%s   ", d);
            c.r = 255;
            c.g = 255;
            c.b = 255;
            c.a = 0;
            graphics_fgcolor(&graphics_root, c);
        } else {
            kprintf("%s   ", d);
            if (k > 8) {
                kprintf("\n");
                k = 0;
            }
            k++;
        }

        int len = strlen(d) + 1;
        d += len;
        length -= len;
    }
    kprintf("\n");
    return 0;
}

static int kshell_listdir(const char *path) {
    struct fs_dirent *d = fs_resolve(path);
    if (d) {
        int buffer_length = 1024;
        char *buffer = kmalloc(buffer_length);
        if (buffer) {
            int length = fs_dirent_list(d, buffer, buffer_length);
            if (length >= 0) {
                kshell_printdir(buffer, length);
            } else {
                kprintf("ls: %s: not a directory\n", path);
            }
            kfree(buffer);
        }
    } else {
        if (path != ".") {
            kprintf("ls: file/directory %s does not exist in the current "
                    "directory\n",
                    path);
        } else {
            kprintf("ls: root directory not found.");
        }
    }

    return 0;
}

static void kshell_print_prompt() {
    struct graphics_color g;
    g.a = 0;
    g.r = 130;
    g.g = 244;
    g.b = 130;
    graphics_fgcolor(&graphics_root, g);
    kprintf("%s@%s", default_shell->user_login_name,
            default_shell->device_name);

    g.a = 0;
    g.b = 255;
    g.r = 255;
    g.g = 255;
    graphics_fgcolor(&graphics_root, g);
    kprintf(":");

    g.a = 0;
    g.b = 250;
    g.g = 200;
    g.r = 100;
    graphics_fgcolor(&graphics_root, g);
    kprintf("%s", default_shell->current_directory);
    g.a = 0;
    g.b = 255;
    g.r = 255;
    g.g = 255;
    graphics_fgcolor(&graphics_root, g);
    kprintf("%s ", promptsym[prompt]);
}

static int kshell_execute(int argc, const char **argv) {
    const char *cmd = argv[0];

    if (!strcmp(cmd, "start")) {
        if (argc > 1) {
            int pid = sys_process_run(argv[1], argc - 1, &argv[1]);
            if (pid > 0) {
#ifdef SHOW_DEBUG_INFO
                kprintf("started process %d\n", pid);
#endif
                process_yield();
            } else {
                kprintf("run: error: cannot start %s\n", argv[1]);
            }
        } else {
            kprintf("run: requires argument.\n");
        }
    } else if (!strcmp(cmd, "exec")) {
        if (argc > 1) {
            sys_process_exec(argv[1], argc - 1, &argv[1]);
            process_yield();
            kprintf("exec: error: couldn't execute %s\n", argv[1]);
        } else {
            kprintf("exec: requires argument.\n");
        }
    } else if (!strcmp(cmd, "run")) {
        if (argc > 1) {
            int pid = sys_process_run(argv[1], argc - 1, &argv[1]);
            if (pid > 0) {
#ifdef SHOW_DEBUG_INFO
                kprintf("started process %d\n", pid);
#endif
                process_yield();
                struct process_info info;
                process_wait_child(pid, &info, -1);
#ifdef SHOW_DEBUG_INFO
                kprintf("process %d exited with status %d\n", info.pid,
                        info.exitcode);
#endif
                process_reap(info.pid);
            } else {
                kprintf("run: error: cannot find %s\n", argv[1]);
            }
        } else {
            kprintf("run: requires argument\n");
        }
    } else if (!strcmp(cmd, "mount")) {
        if (argc == 4) {
            int unit;
            if (str2int(argv[2], &unit)) {
                kshell_mount(argv[1], unit, argv[3]);
            } else {
                kprintf("mount: expected unit number but got %s\n", argv[2]);
            }
        } else {
            kprintf("usage: mount <device> <unit> <fstype>\n");
        }
    } else if (!strcmp(cmd, "umount")) {
        if (current->root_dir) {
            kprintf("umount: unmounting root directory\n");
            fs_dirent_close(current->root_dir);
            current->root_dir = 0;
        } else {
            kprintf("umount: nothing currently mounted\n");
        }
    } else if (!strcmp(cmd, "reap")) {
        if (argc > 1) {
            int pid;
            if (str2int(argv[1], &pid)) {
                if (process_reap(pid)) {
                    kprintf("reap failed!\n");
                } else {
                    kprintf("process %d reaped\n", pid);
                }
            } else {
                kprintf("reap: expected process id but got %s\n", argv[1]);
            }
        } else {
            kprintf("reap: requires argument\n");
        }
    } else if (!strcmp(cmd, "addcmd")) {
        if (argc > 2) {
            comd = argv[1];
            excpath = argv[2];
        } else {
            kprintf("usage: addcmd <command> <path>");
        }
    } else if (!strcmp(cmd, comd)) {
        if (strcmp(excpath, "")) {
            int pid = sys_process_run(excpath, argc - 1, &argv[1]);
            process_yield();
            struct process_info info;
            process_wait_child(pid, &info, -1);
            process_reap(info.pid);
        }
    } else if (!strcmp(cmd, "kill")) {
        if (argc > 1) {
            int pid;
            if (str2int(argv[1], &pid)) {
                process_kill(pid);
            } else {
                kprintf("kill: expected process id number but got %s\n",
                        argv[1]);
            }
        } else {
            kprintf("kill: you need to specify the PID of which program to "
                    "kill.\n");
        }
    } else if (!strcmp(cmd, "wait")) {
        struct process_info info;
        if (process_wait_child(0, &info, 5000) > 0) {
            kprintf("process %d exited with status %d\n", info.pid,
                    info.exitcode);
        } else {
            kprintf("wait: timeout\n");
        }
    } else if (!strcmp(cmd, "ls")) {
        if (argc > 1) {
            kshell_listdir(argv[1]);
        } else {
            kshell_listdir(".");
        }
    } else if (!strcmp(cmd, "memstats")) {
        uint32_t nfree, ntotal;
        page_stats(&nfree, &ntotal);
        kprintf("memstats: memory info: %d/%d KB\n", nfree / 1000,
                ntotal / 1000);
    } else if (!strcmp(cmd, "mkdir")) {
        if (argc == 3) {
            struct fs_dirent *dir = fs_resolve(argv[1]);
            if (dir) {
                struct fs_dirent *n = fs_dirent_mkdir(dir, argv[2]);
                if (!n) {
                    kprintf("mkdir: couldn't create %s\n", argv[2]);
                }
                fs_dirent_close(n);
                fs_dirent_close(dir);
            } else {
                kprintf("mkdir: couldn't open %s\n", argv[1]);
            }
        } else {
            kprintf("usage: mkdir <parent-dir> <dirname>\n");
        }
    } else if (!strcmp(cmd, "format")) {
        if (argc == 4) {
            int unit;
            if (str2int(argv[2], &unit)) {
                struct fs *f = fs_lookup(argv[3]);
                if (f) {
                    struct device *d = device_open(argv[1], unit);
                    if (d) {
                        fs_volume_format(f, d);
                    } else {
                        kprintf("format: couldn't open device %s unit %d\n",
                                argv[1], unit);
                    }
                } else {
                    kprintf("format: invalid fs type: %s\n", argv[3]);
                }
            } else {
                kprintf("format: expected unit number but got %s\n", argv[2]);
            }
        } else {
            kprintf("usage: format <device> <unit> <fstype>\n");
        }
    } else if (!strcmp(cmd, "install")) {
        if (argc == 3) {
            int src, dst;
            str2int(argv[1], &src);
            str2int(argv[2], &dst);
            kshell_install(src, dst);
        } else {
            kprintf("install: expected unit #s for cdrom and disk\n");
        }
    } else if (!strcmp(cmd, "serialwrite")) {
        if (argc == 2) {
            dbg_printf("%s", argv[1]);
        } else {
            kprintf("usage: serialwrite [-r] [message ...]\n");
        }
    } else if (!strcmp(cmd, "serialrecv")) {
        char *data;
        kprintf("serialrecv: press ESC on serial console to stop listening "
                "from serial port\n");
        while (data != ASCII_ESC) {
            serial_device_read(0, data, 1, 0);
            kprintf("%s", data);
        }
    } else if (!strcmp(cmd, "crash")) {
        // Try to perform an invalid action
        kmalloc(0xFFFFFFFF);
    } else if (strew(cmd, "\\")) {
        char *line;
        kshell_readline(&line, 1024, 1);
        int argc = 0;
        char *argv;
        argv[argc] = strtok(line, " ");
        while (argv[argc]) {
            argc++;
            argv[argc] = strtok(0, " ");
        }

        if (argc > 0) {
            kshell_execute(argc, argv); // Recursion
        }
    } else if (!strcmp(cmd, "rm")) {
        if (argc == 3) {
            struct fs_dirent *dir = fs_resolve(argv[1]);
            if (dir) {
                int result = fs_dirent_remove(dir, argv[2]);
                if (result < 0) {
                    kprintf("rm: couldn't remove %s\n", argv[2]);
                }
                fs_dirent_close(dir);
            } else {
                kprintf("rm: couldn't open %s\n", argv[1]);
            }
        } else {
            kprintf("usage: rm <parent-dir> <filename>\n\n");
        }
    } else if (!strcmp(cmd, "cd")) {
        if (argc == 2) {
            int cd_res = sys_chdir(argv[1]);
            if (cd_res == KERROR_INVALID_PATH) {
                kprintf("%s: invalid path specified\n", argv[1]);
            } else if (cd_res == KERROR_NOT_FOUND) {
                kprintf("cd: %s: no such file or directory\n", argv[1]);
            } else if (cd_res == KERROR_NOT_A_DIRECTORY) {
                kprintf("cd: %s: not a directory\n", argv[1]);
            } else {
                default_shell->current_directory = "";
                if (!strcmp(argv[1], ".."))
                    default_shell->current_directory = "/";
                else
                    default_shell->current_directory = argv[1];
            }
        } else if (argc == 1) {
            sys_chdir("/");
        }

        else {
            kprintf("usage: cd <dir>\n\n");
        }
    } else if (!strcmp(cmd, "time")) {
        struct rtc_time time;
        char a = -1;
        rtc_read(&time);
        if (argc > 1) {
            if (!strcmp(argv[1], "--realtime")) {
                while (a == -1) {
                    a = keyboard_read(1);
                    rtc_read(&time);
                    kprintf("\r%d-%d-%d %d:%d:%d", time.year, time.month,
                            time.day, time.hour, time.minute, time.second);
                }
            }
        } else {
            kprintf("%d-%d-%d %d:%d:%d\n", time.year, time.month, time.day,
                    time.hour, time.minute, time.second);
        }
        kprintf("\n");
    } else if (!strcmp(cmd, "reboot")) {
        reboot_system();
    } else if (!strcmp(cmd, "bcache_stats")) {
        struct bcache_stats stats;
        bcache_get_stats(&stats);
        kprintf("%d rhit %d rmiss %d whit %d wmiss %d wback\n", stats.read_hits,
                stats.read_misses, stats.write_hits, stats.write_misses,
                stats.writebacks);
    } else if (!strcmp(cmd, "bcache_flush")) {
        bcache_flush_all();
    } else if (!strcmp(cmd, "help")) {
        kprintf("Cadex KShell, version 1.0.32(1)-release (i686-pc-cadex)\n");
        kprintf("These shell commands are defined internally. Type `help' to "
                "see this list.\n");
        kprintf("Use `info kshell' to find out more about the shell in "
                "general\n\n");
        kprintf(
            " prompt [type ...]                 whoami [-vh]\n"
            " run [path ...]                    echo [-ne] [arg ...]\n"
            " reap [pid ...]                    start [path ...]\n"
            " wait [n] [timeout ...]            mount [dev] [unit] [fstype]\n"
            " umount [unit]                     format [dev] [unit] [fstype]\n"
            " install [src_unit] [dest_unit]    cd [dir]\n"
            " mkdir [path ...]                  rm [path ...]\n"
            " help [-vd]                        clear\n"
            " uname [-avcr]                     ls [dir|.]\n"
            " bcache_flush                      time\n"
            " bcache_stats                      shutdown\n"
            " reboot                            cat [file ...]"
            " serialwrite [-r] [text ...]       serialrecv\n\n"
            "Type `help' to see this help information.\n");
    } else if (!strcmp(cmd, "whoami")) {
        int pid = sys_process_run("/bin/whoami.exe", argc - 1, argv);
        process_yield();
        struct process_info info;
        process_wait_child(pid, &info, -1);
        process_reap(info.pid);
    } else if (!strcmp(cmd, "longtest")) {
        if (!strcmp(argv[1], "-f")) {
            int i;
            for (i = 0; i < sizeof(shakespeare) / sizeof(char *); i++) {
                kprintf("%s\n", shakespeare[i]);
                sleep(1);
            }
        } else if (!strcmp(argv[1], "-s")) {
            int i;
            for (i = 0; i < sizeof(shakespeare) / sizeof(char *); i++) {
                kprintf("%s\n", shakespeare[i]);
                sleep(3);
            }
        } else {
            kprintf("usage: longtest <speed>\nOptions: -s for slow and -f for "
                    "fast\n");
        }
    }

    else if (!strcmp(cmd, "uname")) {
        int pid = sys_process_run("/bin/uname.exe", argc - 1, &argv[1]);
        process_yield();
        struct process_info info;
        process_wait_child(pid, &info, -1);
        process_reap(info.pid);
    }
    /* Shutdown using ACPI */
    else if (!strcmp(cmd, "shutdown")) {
        // try to shutdown using ACPI
        acpi_power_down();
        // If ACPI method didn't succeed try emulator specific method
        shutdown_vm();
    } else if (!strcmp(cmd, "echo")) {
        for (size_t i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "\\n")) {
                kprintf("\n");
            } else if (!strcmp(argv[i], "$1")) {
                kprintf("%d ", last_run_proc_exitcode);
            } else if (!strcmp(argv[i], "\"")) {
                continue;
            } else if (!strsw("\"", argv[i]) || !strew(argv[i], "\"")) {
                kprintf("%s ", argv[i]);
                continue;
            }

            else {
                kprintf("%s ", argv[i]);
            }
        }
        kprintf("\n");
    }

    else if (!strcmp(cmd, "prompt")) {
        /* This is a very good customisation feature. Ability to change prompt
         * symbol. */
        if (!strcmp(argv[1], "bash")) {
            /* [root@cadex]$ */
            prompt = 1;
        } else if (!strcmp(argv[1], "rootbash")) {
            /* [root@cadex]# */
            prompt = 0;
        } else if (!strcmp(argv[1], "linux")) {
            /* [root@cadex]% */
            prompt = 2;
        } else {
            kprintf("\nusage: prompt [symbol]\n\nAvailable symbols are:\n $ : "
                    "bash\n # : rootbash\n % : linux\n\n");
        }
    } else if (!strcmp(cmd, "history")) {
        print_array(kshell_history, 0, 2);
    }

    /* Clears the screen */
    else if (!strcmp(cmd, "clear")) {
        int pid = sys_process_run("/bin/cls.exe", argc - 1, &argv[1]);
        process_yield();
        struct process_info info;
        process_wait_child(pid, &info, -1);
        process_reap(info.pid);
    } else if (!strcmp(cmd, "dim")) {

        int pid = sys_process_run("/bin/dim.exe", argc - 1, &argv[1]);
        process_yield();
        struct process_info info;
        process_wait_child(pid, &info, -1);
        process_reap(info.pid);
    }

    /* cat: output the contents of a file to the console */
    else if (!strcmp(cmd, "cat")) {
        int pid = sys_process_run("/bin/cat.exe", argc - 1, argv);
        process_yield();
        struct process_info info;
        process_wait_child(pid, &info, -1);
        process_reap(info.pid);
    }
    /* standard, not-so-secure version of sudo */
    else if (!strcmp(cmd, "sudo")) {
        int pid = sys_process_run("/bin/sudo.exe", argc - 1, &argv[1]);
        process_yield();
        struct process_info info;
        process_wait_child(pid, &info, -1);
        process_reap(info.pid);
        if (info.exitcode == 0) {
            current->user = USER_ROOT;
        }
    } else if (!strcmp(cmd, "pwd")) {
        kprintf("%s\n", default_shell->current_directory);
    } else if (!strcmp(cmd, "adlib_test")) {
        Adlib_Test();
    } else {
        if (argc > 0 && strsw(".", argv[0])) {
            // Try to run the process
            int pid = sys_process_run(argv[0], argc - 1, &argv[1]);
            if (pid > 1) {
                process_yield();
                struct process_info info;
                process_wait_child(pid, &info, -1);
                process_reap(info.pid);
                // dbg_printf("[kshell] process %d exited with code %d\n",
                // info.pid, info.exitcode);
                last_process_run = 1;
                last_run_proc_exitcode = info.exitcode;
            } else if (pid == KERROR_NOT_FOUND) {
                // Handle the NOT_FOUND error
                kprintf("%s: No such file or directory\n", argv[0]);
            }
        }

        else {
            kprintf("%s: command not found\n", argv[0]);
        }
    }
    return 0;
}

int kshell_readline(char *line, int length, int text_visible) {
    int i = 0;
    int j = 0;
    while (i < (length - 1)) {
        char c = keyboard_read(0);
        if (c == ASCII_CR) {
            /* ENTER */
            line[i] = 0;
            kprintf("\n");
            return 1;
        } else if (c == ASCII_BS) {
            /* BACKSPACE */
            if (i > 0) {
                if (text_visible)
                    putchar(c);
                i--;
            }
        } else if (c == 0x03) {
            /* CTRL + C */
            if (text_visible)
                kprintf("^C");
            i += 2;
            return 0;
        }else if (c == 0x13)
		{
			/* CTRL + S */
            acpi_power_down();
        } else if (c >= 0x20 && c <= 0x7E) {
            /* A-Z a-z 0-9 */
            if (text_visible)
                putchar(c);
            line[i] = c;
            i++;
            j++;
        }
    }

    return 0;
}

int kshell_launch() {
    int i = 0;
    char line[1024];
    const char *argv[100];
    int argc;

    /* Initialize shell variables */
    default_shell->user_login_name = "root";
    default_shell->device_name = "livecd";
    default_shell->current_directory = "~/";

    /* Run Startup Application */
    int pid = sys_process_run("/bin/stapp.exe", 0, 0);
    process_yield();
    struct process_info info;
    process_wait_child(pid, &info, -1);
    process_reap(info.pid);
    if (info.exitcode != 0) {
        kprintf("error: stapp.exe exited with code %d", info.exitcode);
    }

start:
    kprintf("\n");
    while (1) {
        kshell_print_prompt();
        if (kshell_readline(line, sizeof(line), 1)) {
            kshell_history[i] = line;
            i++;
            argc = 0;
            argv[argc] = strtok(line, " ");
            while (argv[argc]) {
                argc++;
                argv[argc] = strtok(0, " ");
            }

            if (argc > 0) {
                kshell_execute(argc, argv);
            }
        } else {
            goto start;
        }
    }
    // This is to keep the kernel running even after a segfault/exception
    goto start;
}
