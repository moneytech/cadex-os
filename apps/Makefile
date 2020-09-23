
include ../Makefile.config

USER_PROGRAMS= tests.exe box.exe

all: $(USER_PROGRAMS)

%.o: %.cpp
	@gcc -m32 -Wall -c -std=c++17 -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -I ../include -o $@ $<
	@echo "CPP    apps/$<"

%.exe: %.o ../libc/crt0.o ../libc/baselib.a
	@i686-elf-ld -melf_i386 -Ttext 0x80000000 ../libc/cxxrt0.o $< ../libc/baselib.a -o $@

clean:
	@rm -rf *.exe *.o
