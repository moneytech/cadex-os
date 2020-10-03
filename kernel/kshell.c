/*
Copyright (C) 2019-2020 OpenCreeck
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "kernel/types.h"
#include "kernel/error.h"
#include "kernel/ascii.h"
#include "library/syscalls.h"
#include "kshell.h"
#include "keyboard.h"
#include "console.h"
#include "string.h"
#include "rtc.h"
#include "kmalloc.h"
#include "page.h"
#include "process.h"
#include "main.h"
#include "fs.h"
#include "fs_internal.h"
#include "syscall_handler.h"
#include "clock.h"
#include "kernelcore.h"
#include "bcache.h"
#include "printf.h"
#include "library/syscalls.h"
#include "library/stdio.h"
#include "library/string.h"
#include "kernel/syscall.h"
#include "kernel/stats.h"
#include "kernel/gfxstream.h"
#include "graphics.h"
#include "interrupt.h"
#include "font.h"
#include "utils.h"
#include "scanf.h"
#include "serial.h"
#include "acpi.h"
#include "module.h"
#include "kernel/sysinfo.h"
#include <library/version.h>
#include <bits/cwd.h>

#define BASEPORT 0x0060 /* lp1 */
#define COM1 0x3f8		/* COM1 Port Address */

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

void reboot_system()
{
	uint8_t temp;

	asm volatile("cli"); /* disable all interrupts */

	/* Clear all keyboard buffers (output and command buffers) */
	do
	{
		temp = inb(KBRD_INTRFC); /* empty user data */
		if (check_flag(temp, KBRD_BIT_KDATA) != 0)
			inb(KBRD_IO); /* empty keyboard data */
	} while (check_flag(temp, KBRD_BIT_UDATA) != 0);

	outb(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */

	reboot(); /* if that didn't work, reboot using the function in kernelcore.S (Triple fault method) */
}

int kshell_readline(char *line, int length);
void print_array(char arr[], int start, int len)
{
	/* Recursion base condition */
	if (start >= len)
		return;

	/* Prints the current array element */
	printf("%s, ", arr[start]);

	/* Recursively call print_array to print next element in array */
	print_array(arr, start - 1, len);
}

void kshell_history_insert(char *str)
{
	if (kshell_history_count == SHELL_HISTORY_ENTRIES)
	{
		kfree(kshell_history[kshell_history_offset]);
		kshell_history[kshell_history_offset] = str;
		kshell_history_offset = (kshell_history_offset + 1) % SHELL_HISTORY_ENTRIES;
	}
	else
	{
		kshell_history[kshell_history_count] = str;
		kshell_history_count++;
	}
}

char *
kshell_history_get(size_t item)
{
	return kshell_history[(item + kshell_history_offset) % SHELL_HISTORY_ENTRIES];
}

char *
kshell_history_prev(size_t item)
{
	return kshell_history_get(kshell_history_count - item);
}
int strEndsWith(const char *str, const char *suffix)
{
	if (!str || !suffix)
		return false;
	size_t lenstr = strlen(str);
	size_t lensuffix = strlen(suffix);
	if (lensuffix > lenstr)
		return false;
	return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}
int memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned char *su1, *su2;
	int res = 0;

	for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}
int strStartsWith(const char *pre, const char *str)
{
	size_t lenpre = strlen(pre),
		   lenstr = strlen(str);
	return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}
void KPANIC(char *str)
{
	printf("[PANIC]: %s\n", str);
}
int kshell_mount(const char *devname, int unit, const char *fs_type)
{
	struct device *dev = device_open(devname, unit);
	if (dev)
	{
		struct fs *fs = fs_lookup(fs_type);
		if (fs)
		{
			struct fs_volume *v = fs_volume_open(fs, dev);
			if (v)
			{
				struct fs_dirent *d = fs_volume_root(v);
				if (d)
				{
					if (current->root_dir)
						fs_dirent_close(current->root_dir);
					current->root_dir = d;
					current->current_dir = fs_dirent_addref(d);
					return 0;
				}
				else
				{
					printf("mount: couldn't find root dir on %s unit %d!\n", device_name(dev), device_unit(dev));
					return -1;
				}
				fs_volume_close(v);
			}
			else
			{
				printf("mount: couldn't mount %s on %s unit %d\n", fs_type, device_name(dev), device_unit(dev));
				return -1;
			}
		}
		else
		{
			printf("mount: invalid fs type: %s\n", fs_type);
			return -1;
		}
		device_close(dev);
	}
	else
	{
		printf("mount: couldn't open device %s unit %d\n", devname, unit);
		return -1;
	}

	return -1;
}
static int kshell_mount_nomsg(const char *devname, int unit, const char *fs_type)
{
	struct device *dev = device_open(devname, unit);
	if (dev)
	{
		struct fs *fs = fs_lookup(fs_type);
		if (fs)
		{
			struct fs_volume *v = fs_volume_open(fs, dev);
			if (v)
			{
				struct fs_dirent *d = fs_volume_root(v);
				if (d)
				{
					if (current->root_dir)
						fs_dirent_close(current->root_dir);
					current->root_dir = d;
					current->current_dir = fs_dirent_addref(d);
					return 0;
				}
				else
				{
					return -1;
				}
				fs_volume_close(v);
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		device_close(dev);
	}
	else
	{
		printf("mount: couldn't open device %s unit %d\n", devname, unit);
		return -1;
	}

	return -1;
}

/*
Install Cadex OS and the softwares from the cdrom volume unit src
to the disk volume dst by performing a recursive copy.
TODO: This needs better error checking.
*/

int kshell_install(int src, int dst)
{
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

	printf("Installing Cadex OS on disk (copying from atapi unit %d and copying to ata unit %d)...\n", src, dst);
	dbg_printf("[kshell] copying atapi unit %d contents to ata unit %d...\n", src, dst);
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

static int kshell_printdir(const char *d, int length)
{
	int k = 0;
	while (length > 0)
	{
		struct graphics_color *c;
		if (!strcmp(d, ".") || !strcmp(d, ".."))
		{
			printf("%s\n", d);
		}
		// Highlighting executable files has a bug
		else if (strEndsWith(d, ".exe"))
		{
			// c->r = 130;
			// c->g = 244;
			// c->b = 130;
			// graphics_fgcolor(&graphics_root, *c);
			printf("%s   ", d);
			// c->r = 255;
			// c->g = 255;
			// c->b = 255;
			// graphics_fgcolor(&graphics_root, *c);
		}
		else
		{
			printf("%s   ", d);
			if (k > 8)
			{
				printf("\n");
				k = 0;
			}
			k++;
		}

		int len = strlen(d) + 1;
		d += len;
		length -= len;
	}
	printf("\n");
	return 0;
}

static int kshell_listdir(const char *path)
{
	struct fs_dirent *d = fs_resolve(path);
	if (d)
	{
		int buffer_length = 1024;
		char *buffer = kmalloc(buffer_length);
		if (buffer)
		{
			int length = fs_dirent_list(d, buffer, buffer_length);
			if (length >= 0)
			{
				kshell_printdir(buffer, length);
			}
			else
			{
				printf("ls: %s: not a directory\n", path);
			}
			kfree(buffer);
		}
	}
	else
	{
		if (path != ".")
		{
			printf("ls: file/directory %s does not exist in the current directory\n", path);
		}
		else
		{
			printf("ls: root directory not found.");
		}
	}

	return 0;
}

static int kshell_execute(int argc, const char **argv)
{
	const char *cmd = argv[0];

	if (!strcmp(cmd, "start"))
	{
		if (argc > 1)
		{
			int pid = sys_process_run(argv[1], argc - 1, &argv[1]);
			if (pid > 0)
			{
#ifdef SHOW_DEBUG_INFO
				printf("started process %d\n", pid);
#endif
				process_yield();
			}
			else
			{
				printf("run: error: cannot start %s\n", argv[1]);
			}
		}
		else
		{
			printf("run: requires argument.\n");
		}
	}
	else if (!strcmp(cmd, "exec"))
	{
		if (argc > 1)
		{
			sys_process_exec(argv[1], argc - 1, &argv[1]);
			process_yield();
			printf("exec: error: couldn't execute %s\n", argv[1]);
		}
		else
		{
			printf("exec: requires argument.\n");
		}
	}
	else if (!strcmp(cmd, "run"))
	{
		if (argc > 1)
		{
			int pid = sys_process_run(argv[1], argc - 1, &argv[1]);
			if (pid > 0)
			{
#ifdef SHOW_DEBUG_INFO
				printf("started process %d\n", pid);
#endif
				process_yield();
				struct process_info info;
				process_wait_child(pid, &info, -1);
#ifdef SHOW_DEBUG_INFO
				printf("process %d exited with status %d\n", info.pid, info.exitcode);
#endif
				process_reap(info.pid);
			}
			else
			{
				printf("run: error: cannot find %s\n", argv[1]);
			}
		}
		else
		{
			printf("run: requires argument\n");
		}
	}
	else if (!strcmp(cmd, "mount"))
	{
		if (argc == 4)
		{
			int unit;
			if (str2int(argv[2], &unit))
			{
				kshell_mount(argv[1], unit, argv[3]);
			}
			else
			{
				printf("mount: expected unit number but got %s\n", argv[2]);
			}
		}
		else
		{
			printf("usage: mount <device> <unit> <fstype>\n");
		}
	}
	else if (!strcmp(cmd, "umount"))
	{
		if (current->root_dir)
		{
			printf("umount: unmounting root directory\n");
			fs_dirent_close(current->root_dir);
			current->root_dir = 0;
		}
		else
		{
			printf("umount: nothing currently mounted\n");
		}
	}
	else if (!strcmp(cmd, "reap"))
	{
		if (argc > 1)
		{
			int pid;
			if (str2int(argv[1], &pid))
			{
				if (process_reap(pid))
				{
					printf("reap failed!\n");
				}
				else
				{
					printf("process %d reaped\n", pid);
				}
			}
			else
			{
				printf("reap: expected process id but got %s\n", argv[1]);
			}
		}
		else
		{
			printf("reap: requires argument\n");
		}
	}
	else if (!strcmp(cmd, "addcmd"))
	{
		if (argc > 2)
		{
			comd = argv[1];
			excpath = argv[2];
		}
		else
		{
			printf("usage: addcmd <command> <path>");
		}
	}
	else if (!strcmp(cmd, comd))
	{
		if (strcmp(excpath, ""))
		{
			int pid = sys_process_run(excpath, argc - 1, &argv[1]);
			process_yield();
			struct process_info info;
			process_wait_child(pid, &info, -1);
			process_reap(info.pid);
		}
	}
	else if (!strcmp(cmd, "kill"))
	{
		if (argc > 1)
		{
			int pid;
			if (str2int(argv[1], &pid))
			{
				process_kill(pid);
			}
			else
			{
				printf("kill: expected process id number but got %s\n", argv[1]);
			}
		}
		else
		{
			printf("kill: you need to specify the PID of which program to kill.\n");
		}
	}
	else if (!strcmp(cmd, "wait"))
	{
		struct process_info info;
		if (process_wait_child(0, &info, 5000) > 0)
		{
			printf("process %d exited with status %d\n", info.pid, info.exitcode);
		}
		else
		{
			printf("wait: timeout\n");
		}
	}
	else if (!strcmp(cmd, "ls"))
	{
		if (argc > 1)
		{
			kshell_listdir(argv[1]);
		}
		else
		{
			kshell_listdir(".");
		}
	}
	else if (!strcmp(cmd, "memstats"))
	{
		uint32_t nfree, ntotal;
		page_stats(&nfree, &ntotal);
		printf("memstats: memory info: %d/%d B\n", nfree, ntotal);
	}
	else if (!strcmp(cmd, "mkdir"))
	{
		if (argc == 3)
		{
			struct fs_dirent *dir = fs_resolve(argv[1]);
			if (dir)
			{
				struct fs_dirent *n = fs_dirent_mkdir(dir, argv[2]);
				if (!n)
				{
					printf("mkdir: couldn't create %s\n", argv[2]);
				}
				fs_dirent_close(n);
				fs_dirent_close(dir);
			}
			else
			{
				printf("mkdir: couldn't open %s\n", argv[1]);
			}
		}
		else
		{
			printf("usage: mkdir <parent-dir> <dirname>\n");
		}
	}
	else if (!strcmp(cmd, "format"))
	{
		if (argc == 4)
		{
			int unit;
			if (str2int(argv[2], &unit))
			{
				struct fs *f = fs_lookup(argv[3]);
				if (f)
				{
					struct device *d = device_open(argv[1], unit);
					if (d)
					{
						fs_volume_format(f, d);
					}
					else
					{
						printf("format: couldn't open device %s unit %d\n", argv[1], unit);
					}
				}
				else
				{
					printf("format: invalid fs type: %s\n", argv[3]);
				}
			}
			else
			{
				printf("format: expected unit number but got %s\n", argv[2]);
			}
		}
		else
		{
			printf("usage: format <device> <unit> <fstype>\n");
		}
	}
	else if (!strcmp(cmd, "install"))
	{
		if (argc == 3)
		{
			int src, dst;
			str2int(argv[1], &src);
			str2int(argv[2], &dst);
			kshell_install(src, dst);
		}
		else
		{
			printf("install: expected unit #s for cdrom and disk\n");
		}
	}
	else if (!strcmp(cmd, "serialsend"))
	{
		if (argc == 2)
		{
			serial_device_write(0, argv[1], strlen(argv[1]), 0);
		}
		else
		{
			printf("usage: serialsend <message>\n");
		}
	}
	else if (!strcmp(cmd, "serialrecv"))
	{
		char *data;
		while (1)
		{
			serial_device_read(0, data, 1, 0);
			/* code */
			printf("%s", data);
		}
	}

	else if (strEndsWith(cmd, "\\"))
	{
		char *line;
		printf("> ");
		kshell_readline(&line, 1024);
		int argc = 0;
		char *argv;
		argv[argc] = strtok(line, " ");
		while (argv[argc])
		{
			argc++;
			argv[argc] = strtok(0, " ");
		}

		if (argc > 0)
		{
			kshell_execute(argc, argv); // Recursion
		}
	}
	else if (!strcmp(cmd, "rm"))
	{
		if (argc == 3)
		{
			struct fs_dirent *dir = fs_resolve(argv[1]);
			if (dir)
			{
				int result = fs_dirent_remove(dir, argv[2]);
				if (result < 0)
				{
					printf("rm: couldn't remove %s\n", argv[2]);
				}
				fs_dirent_close(dir);
			}
			else
			{
				printf("rm: couldn't open %s\n", argv[1]);
			}
		}
		else
		{
			printf("usage: rm <parent-dir> <filename>\n\n");
		}
	}
	else if (!strcmp(cmd, "cd"))
	{
		if (argc == 2)
		{
			int cd_res = sys_chdir(argv[1]);
			if (cd_res == KERROR_INVALID_PATH)
			{
				printf("%s: invalid path specified\n", argv[1]);
			}
			else if (cd_res == KERROR_NOT_FOUND)
			{
				printf("cd: %s: no such file or directory\n", argv[1]);
			}
			else if (cd_res == KERROR_NOT_A_DIRECTORY)
			{
				printf("cd: %s: not a directory\n", argv[1]);
			}
			else
			{
				__cwd = "";
				if (!strStartsWith("/", argv[1]) && strcmp(argv[1], ".."))
					__cwd = strcat("/", argv[1]);
			}
		}
		else if (argc == 1)
		{
			sys_chdir("/");
		}

		else
		{
			printf("usage: cd <dir>\n\n");
		}
	}
	else if (!strcmp(cmd, "time"))
	{
		struct rtc_time time;
		rtc_read(&time);
		printf("%d-%d-%d %d:%d:%d\n", time.year, time.month, time.day, time.hour, time.minute, time.second);
	}
	else if (!strcmp(cmd, "reboot"))
	{
		reboot_system();
	}
	else if (!strcmp(cmd, "qshutdown"))
	{
		shutdown_vm();
		KPANIC("emulators (QEMU) doesn't support shutdown"); // KPANIC if it doesn't shutdown
	}
	else if (!strcmp(cmd, "bcache_stats"))
	{
		struct bcache_stats stats;
		bcache_get_stats(&stats);
		printf("%d rhit %d rmiss %d whit %d wmiss %d wback\n",
			   stats.read_hits, stats.read_misses,
			   stats.write_hits, stats.write_misses,
			   stats.writebacks);
	}
	else if (!strcmp(cmd, "bcache_flush"))
	{
		bcache_flush_all();
	}
	else if (!strcmp(cmd, "help"))
	{
		printf("Cadex OS v0.1.6 Lean Llama\nAvailable commands :\n\n* whoami\n* longtest\n* basic86 <args>\n* prompt <args>\n* sdlg <args>\n* clear\n* uname <args>\n* run <path> <args>\n* whoami\n* start <path> <args>\n* kill <pid>\n* reap <pid>\n* wait\n* ls\n* mount <device> <unit> <fstype>\n* umount\n* format <device> <unit><fstype>\n* install <srcunit> <dstunit>\n* cd <path>\n* mkdir <path>\n* rm <path>\n* time\n* bcache_stats\n* bcache_flush\n* reboot\n* shutdown\n* help\n\n");
	}
	else if (!strcmp(cmd, "whoami"))
	{
		printf("\nroot\n");
	}
	else if (!strcmp(cmd, "longtest"))
	{
		/**
		 * Long character test
		 * Only for testing purposes
		*/
		if (!strcmp(argv[1], "-f"))
		{
			int i;
			for (i = 0; i < sizeof(shakespeare) / sizeof(char *); i++)
			{
				printf("%s\n", shakespeare[i]);
				sleep(1);
			}
		}
		else if (!strcmp(argv[1], "-s"))
		{
			int i;
			for (i = 0; i < sizeof(shakespeare) / sizeof(char *); i++)
			{
				printf("%s\n", shakespeare[i]);
				sleep(3);
			}
		}
		else
		{
			printf("usage: longtest <speed>\nOptions: -s for slow and -f for fast\n");
		}
	}

	else if (!strcmp(cmd, "uname"))
	{
		int pid = sys_process_run("/bin/uname.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	/* Shutdown using ACPI */
	else if (!strcmp(cmd, "shutdown"))
	{
		acpi_power_down();
	}
	else if (!strcmp(cmd, "echo"))
	{
		for (size_t i = 1; i < argc; i++)
		{
			if (!strcmp(argv[i], "\\n"))
			{
				printf("\n");
			}
			else if (!strcmp(argv[i], "$1"))
			{
				printf("%d ", last_run_proc_exitcode);
			}
			else if (!strcmp(argv[i], "\""))
			{
				continue;
			}
			else if (!strStartsWith("\"", argv[i]) || !strEndsWith(argv[i], "\""))
			{
				printf("%s ", argv[i]);
				continue;
			}

			else
			{
				printf("%s ", argv[i]);
			}
		}
		printf("\n");
	}

	else if (!strcmp(cmd, "prompt"))
	{
		/* This is a very good customisation feature. Ability to change prompt symbol. */
		if (!strcmp(argv[1], "bash"))
		{
			/* [root@cadex]$ */
			prompt = 1;
		}
		else if (!strcmp(argv[1], "rootbash"))
		{
			/* [root@cadex]# */
			prompt = 0;
		}
		else if (!strcmp(argv[1], "linux"))
		{
			/* [root@cadex]% */
			prompt = 2;
		}
		else
		{
			printf("\nusage: prompt [symbol]\n\nAvailable symbols are:\n $ : bash\n # : rootbash\n % : linux\n\n");
		}
	}
	else if (!strcmp(cmd, "history"))
	{
		print_array(kshell_history, 0, 2);
	}

	/* Clears the screen */
	else if (!strcmp(cmd, "clear"))
	{
		int pid = sys_process_run("/bin/cls.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	else if (!strcmp(cmd, "dim"))
	{

		int pid = sys_process_run("/bin/dim.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}

	/* cat: output the contents of a file to the console */
	else if (!strcmp(cmd, "cat"))
	{
		int pid = sys_process_run("/bin/cat.exe", argc - 1, argv);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	/* standard, not-so-secure version of sudo */
	else if (!strcmp(cmd, "sudo"))
	{
		int pid = sys_process_run("/bin/sudo.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
		if (info.exitcode == 0)
		{
			current->user = USER_ROOT;
		}
	}
	else if (!strcmp(cmd, "pwd"))
	{
		printf("%s, %s", _cwd_, __cwd);
	}
	else if (!strcmp(cmd, "mousetest"))
	{
		struct mouse_event m;
	}

	else
	{
		// strStartsWith is required or every time you type a wrong command, it will say file not found
		if (argc > 0 && strStartsWith(".", argv[0]))
		{
			// Try to run the process
			int pid = sys_process_run(argv[0], argc - 1, &argv[1]);
			if (pid > 1)
			{
				process_yield();
				struct process_info info;
				process_wait_child(pid, &info, -1);
				process_reap(info.pid);
				dbg_printf("\001b[32m[kshell]\001b[0m process %d exited with code %d\n", info.pid, info.exitcode);
				last_process_run = 1;
				last_run_proc_exitcode = info.exitcode;
			}
			else if (pid == KERROR_NOT_FOUND)
			{
				// Handle the NOT_FOUND error
				printf("%s: No such file or directory\n", argv[0]);
			}
		}

		else
		{
			printf("%s: command not found\n", argv[0]);
		}
	}
	return 0;
}

int kshell_readline(char *line, int length)
{
	int i = 0;
	int j = 0;
	while (i < (length - 1))
	{
		char c = keyboard_read(0);
		if (c == ASCII_CR)
		{
			line[i] = 0;
			printf("\n");
			return 1;
		}
		else if (c == ASCII_BS)
		{
			if (i > 0)
			{
				putchar(c);
				i--;
			}
		}
		else if (c >= 0x20 && c <= 0x7E)
		{
			putchar(c);
			line[i] = c;
			i++;
			j++;
		}
	}

	return 0;
}

uint32_t random(uint32_t min, uint32_t max)
{
	static uint32_t state = 0xF3DC1A24;
	state = (state * 1299721) + 29443;
	return min + ((state >> 16) % (max - min + 1));
}

int kshell_launch()
{

	int i = 0;
	char line[1024];
	const char *argv[100];
	int argc;
start:
	printf("\n");
	while (1)
	{
		printf("[root@cadex:/]%s ", promptsym[prompt]);
		kshell_readline(line, sizeof(line));
		kshell_history[i] = line;
		i++;
		argc = 0;
		argv[argc] = strtok(line, " ");
		while (argv[argc])
		{
			argc++;
			argv[argc] = strtok(0, " ");
		}

		if (argc > 0)
		{
			kshell_execute(argc, argv);
		}
	}
	// This is to keep the kernel running even after a segfault/exception
	goto start;
}
