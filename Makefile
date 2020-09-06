# Cadex OS Build Makefile for i386 architecture.
include Makefile.config

LIBRARY_SOURCES=$(wildcard libc/*.c)
LIBRARY_HEADERS=$(wildcard libc/*.h)
LIBCPP_SOURCES=$(wildcard lib/*.cpp)
LIBCPP_HEADERS=$(wildcard lib/*.h)
USER_SOURCES=$(wildcard usr/*.c)
APPS_SOURCES=$(wildcard apps/*.cpp)
SYSTEM_BIN_SOURCES=$(wildcard bin/*.c)
USER_PROGRAMS=$(USER_SOURCES:c=exe)
SYSTEM_BIN_FILES=$(SYSTEM_BIN_SOURCES:c=exe)
APPS_BINARIES=$(APPS_SOURCES:cpp=exe)
KERNEL_SOURCES=$(wildcard kernel/*.[chS])

MAKEFLAGS += --no-print-directory

all: clear clean cadex.iso success # run # Uncomment this run command to run the OS after you've built the OS

run: cadex.iso
					# See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
	qemu-system-i386.exe -cdrom cadex.iso -m size=500M -drive 'file=disk.img,format=qcow2' -device isa-debug-exit,iobase=0xf3,iosize=0x04 || qemu-system-i386 -cdrom cadex.iso -m size=500M -drive 'file=disk.img,format=raw' -hda disk.img -device isa-debug-exit,iobase=0xf4,iosize=0x04

debug: cadex.iso hddimg
					# See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
	qemu-system-i386.exe -cdrom cadex.iso -s -S &

hddimg:
	qemu-img create -f qcow2 disk.img 1G

libc/baselib.a: $(LIBRARY_SOURCES) $(LIBRARY_HEADERS)
	@cd libc && make ${MAKEFLAGS}

lib/stdcpplib.a: $(LIBCPP_SOURCES) $(LIBCPP_HEADERS)
	@cd lib && make ${MAKEFLAGS}

$(USER_PROGRAMS): $(USER_SOURCES) libc/baselib.a $(LIBRARY_HEADERS)
	@cd usr && make ${MAKEFLAGS}

$(SYSTEM_BIN_FILES): $(SYSTEM_BIN_SOURCES) libc/baselib.a $(LIBRARY_HEADERS)
	@cd bin && make ${MAKEFLAGS}

$(APPS_BINARIES): $(APPS_SOURCES) libc/baselib.a lib/stdcpplib.a $(LIBRARY_HEADERS) $(LIBCPP_HEADERS)
	@cd apps && make ${MAKEFLAGS}

kernel/cadex.img: $(KERNEL_SOURCES) $(LIBRARY_HEADERS)
	@cd kernel && make ${MAKEFLAGS}

image: kernel/cadex.img $(USER_PROGRAMS) $(SYSTEM_BIN_FILES) $(APPS_BINARIES)
	@rm -rf image
	@mkdir image image/boot image/usr image/data image/usr/bin image/bin image/sys image/usr/share image/etc image/var image/tmp image/usr/apps
	@cp kernel/cadex.img image/boot
	@cd basefs && make
	@cp $(USER_PROGRAMS) image/usr/bin
	@cp $(SYSTEM_BIN_FILES) image/bin
	@cp $(APPS_BINARIES) image/usr/apps
	@head -2000 /usr/share/dict/words > image/data/words

cadex.iso: image
	@${ISOGEN} -input-charset utf-8 -iso-level 2 -J -R -o $@ -b boot/cadex.img image
	@echo "Building ISO image..."
	@rm -rf image

success:
	@echo "\nBuild finished. Type 'make run' to run\n"

clean:
	@rm -rf cadex.iso image
	@cd kernel && make clean
	@cd libc && make clean
	@cd usr && make clean
	@cd bin && make clean

clear:
	@clear
