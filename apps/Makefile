
include ../arch/i386/Makefile.config

USER_PROGRAMS= tests.exe \
			   box.exe \
			   api_example.exe \
			   calc.exe \
			   templeos.exe

all: alert $(USER_PROGRAMS)

%.o: %.cpp
	@${CPP} -m32 -w -c -std=c++17 -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -I ../include -o $@ $<
	@echo " CXX    apps/$<"

%.exe: %.o ../libc/crt/cxxrt0.o ../libc/baselib.a
	@i686-elf-ld -melf_i386 -Ttext 0x80000000 ../libc/crt/cxxrt0.o $< ../libc/baselib.a -o $@

alert:
	@echo "-- Building userspace C++ apps (/usr/apps)..."

clean:
	@rm -rf *.exe *.o
