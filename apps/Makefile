
include ../Makefile.config

USER_PROGRAMS= example.exe

all: $(USER_PROGRAMS)

%.o: %.cpp
	@gcc -m32 -Wall -c -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-use-cxa-atexit -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -g -I ../include -o $@ $<
	@echo "CPP     apps/$<"

%.exe: %.o ../libc/user-start.o ../libc/baselib.a ../lib/stdcpplib.a
	@i686-elf-ld -melf_i386 -Ttext 0x80000000 ../libc/user-start.o $< ../libc/baselib.a ../lib/stdcpplib.a -o $@

clean:
	@rm -rf *.exe *.o
