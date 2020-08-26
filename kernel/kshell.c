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
#include "cbasic.h"
#include "serial.h"

#define BASEPORT 0x0060 /* lp1 */

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
char *curdir = "";
int prompt = 0;
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
void move_cursor(uint16_t pos)
{
	outb(0x3D4, 14);
	outb(0x3D5, ((pos >> 8) & 0x00FF));
	outb(0x3D4, 15);
	outb(0x3D5, pos & 0x00FF);
}

void move_cursor_next_line()
{
	cursor_pos = 80 * cursor_next_line_index;
	cursor_next_line_index++;
	move_cursor(cursor_pos);
}
/*
Install software from the cdrom volume unit src
to the disk volume dst by performing a recursive copy.
XXX This needs better error checking.
*/

int kshell_install(int src, int dst)
{
	struct fs *srcfs = fs_lookup("cdromfs");
	struct fs *dstfs = fs_lookup("diskfs");

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

	printf("copying atapi unit %d to ata unit %d...\n", src, dst);
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
	while (length > 0)
	{
		if (!strcmp(d, ".") || !strcmp(d, ".."))
		{
			printf("%s\n", d);
		}
		else
		{
			printf("%s   ", d);
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
				printf("ls: %s is not a directory\n", path);
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
			printf("ls: root directory not found. Possible causes:\n\n * CD-ROM not mounted\n * Hard-Disk error\n * Other filesystem error\n\nTry running 'mount atapi 2 cdromfs' if you are running this OS from a CD-ROM\n");
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
			printf("mount: requires device, unit, and fs type\n");
		}
	}
	else if (!strcmp(cmd, "umount"))
	{
		if (current->root_dir)
		{
			printf("unmounting root directory\n");
			fs_dirent_close(current->root_dir);
			current->root_dir = 0;
		}
		else
		{
			printf("nothing currently mounted\n");
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
	else if (!strcmp(cmd, "stress"))
	{
		while (1)
		{
			const char *argv[] = {"test", "arg1", "arg2", "arg3", "arg4", "arg5", 0};
			int pid = sys_process_run("/bin/test", 6, argv);
			if (pid > 0)
			{
				struct process_info info;
				process_wait_child(pid, &info, -1);
				printf("process %d exited with status %d\n", info.pid, info.exitcode);
				process_reap(pid);
			}
			else
			{
				printf("run failed\n");
				clock_wait(1000);
			}
			uint32_t nfree, ntotal;
			page_stats(&nfree, &ntotal);
			printf("memory: %d/%d\n", nfree, ntotal);
		}
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
			printf("mkdir ver 0.0.3\nUsage: mkdir <parent-dir> <dirname>\n");
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
			printf("rm ver 0.0.5\nUsage: rm <parent-dir> <filename>\n\n");
		}
	}
	else if (!strcmp(cmd, "cd"))
	{
		if (argc == 2)
		{
			sys_chdir(argv[1]);
		}
		else
		{
			printf("cd ver 0.0.3\nUsage: cd <directory>\n\n");
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
		reboot();
	}
	else if (!strcmp(cmd, "shutdown"))
	{
		for (const char *s = "Shutdown"; *s; ++s)
		{
			outb(0x8900, *s);
		}
		printf("Shutting down...\n");
		// Uncomment the line below if you are running this on VirtualBox
		//sleep(150);
		sleep(5);
		outb(0xf4, 0x00);
		printf("Your device BIOS does not support shutdown by 'outb(0xF4, 0x00);'\n");
	}
	else if (!strcmp(cmd, "beep"))
	{
		/* A simple beep implementation. See https://wiki.osdev.org/PC_Speaker#Sample_Code/ /**Code by HyperCreeck**/
		/* May not work in emulators */
		beep();
		printf('\a');
		printf("\n");
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
		printf("Cadex Shell Commands:\n\n* whoami\n* longtest\n* cbas\n* chprompt <args>\n* mkdiag\n* clear\n* uname <args>\n* run <path> <args>\n* pman install <package>\n* pman remove <package>\n* pman reinit\n* pman upgrade <pacgage>\n* whoami\n* start <path> <args>\n* kill <pid>\n* reap <pid>\n* wait\n* ls\n* mount <device> <unit> <fstype>\n* umount\n* format <device> <unit><fstype>\n* install <srcunit> <dstunit>\n* cd <path>\n* mkdir <path>\n* rm <path>\n* time\n* bcache_stats\n* bcache_flush\n* reboot\n* shutdown\n* help\n\n");
	}
	else if (!strcmp(cmd, "pman"))
	{
		printf(">>>>>>>>> Cadex Package Manager <<<<<<<<<<<<\n\nUsage:\n pman install <package name>\n pman remove <package name>\n pman reinit\n pman upgrade <package name>");
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
			printf("Long Char Test Ver 0.0.1\nUsage: longtest <speed>\n-s for slow and -f for fast\n");
		}
	}
	else if (!strcmp(cmd, "unexpected"))
	{

		while (1)
		{
			printf("\-/-\-/");
		}
	}

	else if (!strcmp(cmd, "uname"))
	{
		if (!strcmp(argv[1], "-v"))
		{
		}
		else if (!strcmp(argv[1], "-b"))
		{
			printf("0.0.1B-D");
		}
		else if (!strcmp(argv[1], "-c"))
		{
			printf("Tackling Turbo");
		}
		else if (!strcmp(argv[1], "-a"))
		{
			printf("Cadex OS Version 0.0.1 B-DEB\nTackling Turbo\n 0.0.1\n");
		}
		else if (!strcmp(argv[1], "-v"))
		{
			printf("0.0.1\n");
		}
		else
		{
			printf("Usage: uname <options>\nOptions:\n -v: Version Number\n -b: Build number\n -c: Codename\n -a: All information\n");
		}
	}
	else if (!strcmp(cmd, "dectohex"))
	{
		decToHex();
	}
	else if (!strcmp(cmd, "cdmount"))
	{
		printf("atapi: mounting disk with unit 2 with filesystem cdromfs\n");
		kshell_mount("atapi", 2, "cdromfs");
	}
	else if (!strcmp(cmd, "cbas"))
	{

		cbasic();
	}
	else if (!strcmp(cmd, "chprompt"))
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
		else if (!strcmp(argv[1], "linux-3"))
		{
			/* [root@cadex]% */
			prompt = 2;
		}
		else
		{
			printf("\nCadex chprompt. Utility to change shell prompt symbol.\nAvailable symbols are:\n $ : chprompt bash\n # : chprompt rootbash\n \% : chprompt linux-3\n\n");
		}
	}
	else if (!strcmp(cmd, "serial"))
	{
		static struct mouse_event *state;
		printf("Mouse activated.\n");
		mouse_init();
		while (1)
		{
			mouse_read(state);
			//printChar(state->x, state->y, "hi");
			printf("%d", state->x);
			//ps2_clear_buffer();
		}
	}
	else if (!strcmp(cmd, "mkdiag"))
	{
		int pid = sys_process_run("/bin/mkdiag.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	else if (!strcmp(cmd, "clear"))
	{
		int pid = sys_process_run("/bin/clrscr.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	else if (!strcmp(cmd, "cat"))
	{
		int pid = sys_process_run("/bin/cat.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	else if (!strcmp(cmd, "sudo"))
	{
		int pid = sys_process_run("/bin/sudo.exe", argc - 1, &argv[1]);
		process_yield();
		struct process_info info;
		process_wait_child(pid, &info, -1);
		process_reap(info.pid);
	}
	else
	{
		if (argc > 0)
		{
			int pid = sys_process_run(argv[0], argc - 1, &argv[1]);
			if (pid > 0)
			{
#ifdef DEBUG
				printf("started process %d\n", pid);
#endif // DEBUG
				process_yield();
				struct process_info info;
				process_wait_child(pid, &info, -1);
#ifdef DEBUG
				printf("process %d exited with status %d\n", info.pid, info.exitcode);
#endif // DEBUG
				process_reap(info.pid);
			}
			else
			{
				printf("%s: command/program not found\n", argv[0]);
			}
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
	char line[1024];
	const char *argv[100];
	int argc;
start:
	printf("\n");
	while (1)
	{
		printf("[root@cadex:/%s]%s ", curdir, promptsym[prompt]);
		kshell_readline(line, sizeof(line));

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
