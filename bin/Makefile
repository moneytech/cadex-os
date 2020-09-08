
include ../Makefile.config

USER_PROGRAMS= sdlg.exe \
			   whoami.exe \
			   uname.exe \
			   bounce.exe \
			   clrscr.exe \
			   cat.exe \
			   cash.exe \
			   bshell.exe \
			   basic.exe \
			   sudo.exe \
			   splash.exe \
			   dim.exe \
			   touch.exe \
			   dbusctl.exe

all: $(USER_PROGRAMS)

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC     bin/$<"

# %.o: %.cc
# 	@${CPP} -m32 -Wall -c -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-use-cxa-atexit -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -g -I ../include -o $@ $<
# 	@echo "CPP     bin/$<"

%.exe: %.o ../libc/user-start.o ../libc/baselib.a
	@i686-elf-ld -melf_i386 -Ttext 0x80000000 ../libc/user-start.o $< ../libc/baselib.a -o $@

clean:
	@rm -rf *.exe *.o
