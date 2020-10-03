
include ../Makefile.config

USER_PROGRAMS= sdlg.exe \
			   whoami.exe \
			   uname.exe \
			   bounce.exe \
			   cls.exe \
			   cat.exe \
			   cash.exe \
			   bshell.exe \
			   sudo.exe \
			   splash.exe \
			   dim.exe \
			   touch.exe \
			   dbusctl.exe \
			   base64.exe \
			   cd.exe \
			   klog.exe \
			   check_fs.exe

all: alert $(USER_PROGRAMS)

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo " CC     bin/$<"

# %.o: %.cc
# 	@${CPP} -m32 -Wall -c -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-use-cxa-atexit -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -g -I ../include -o $@ $<
# 	@echo "CPP     bin/$<"

%.exe: %.o ../libc/rt/crt0.o ../libc/baselib.a
	@i686-elf-ld -melf_i386 -Ttext 0x80000000 ../libc/rt/crt0.o $< ../libc/baselib.a -o $@

alert:
	echo "-- Building userspace system utilities (/bin)..."

clean:
	@rm -rf *.exe *.o
