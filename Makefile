# Cadex OS Build Makefile for i386 architecture.
include Makefile.config

LIBRARY_SOURCES=$(wildcard libc/*.c)
LIBRARY_HEADERS=$(wildcard libc/*.h)
USER_SOURCES=$(wildcard usr/*.c)
APPS_SOURCES=$(wildcard apps/*.cpp)
SYSTEM_BIN_SOURCES=$(wildcard bin/*.c)
USER_PROGRAMS=$(USER_SOURCES:c=exe)
SYSTEM_BIN_FILES=$(SYSTEM_BIN_SOURCES:c=exe)
APPS_BINARIES=$(APPS_SOURCES:cpp=exe)
KERNEL_SOURCES=$(wildcard kernel/*.[chS])

ISO_FILENAME = cadexos-image.iso

MAKEFLAGS += --no-print-directory

all: clear clean ${ISO_FILENAME} success

run: cadex.iso
	@echo " -- Using ${ISO_FILENAME}"
	@qemu-system-i386.exe -cdrom ${ISO_FILENAME} -m size=500M -drive 'file=hard_disk.img,format=qcow2' -device isa-debug-exit,iobase=0xf3,iosize=0x04

debug: cadex.iso hddimg
	@qemu-system-i386.exe -cdrom ${ISO_FILENAME} -s -S & gdb

hddimg:
	@qemu-img create -f qcow2 hard_disk.img 1G

libc/baselib.a: $(LIBRARY_SOURCES) $(LIBRARY_HEADERS)
	@cd libc && make ${MAKEFLAGS}

$(USER_PROGRAMS): $(USER_SOURCES) libc/baselib.a $(LIBRARY_HEADERS)
	@cd usr && make ${MAKEFLAGS}

$(SYSTEM_BIN_FILES): $(SYSTEM_BIN_SOURCES) libc/baselib.a $(LIBRARY_HEADERS)
	@cd bin && make ${MAKEFLAGS}

$(APPS_BINARIES): $(APPS_SOURCES) libc/baselib.a $(LIBRARY_HEADERS)
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

${ISO_FILENAME}: image
	@echo "-- Building ISO image (${ISO_FILENAME})..."
	@${ISOGEN} -input-charset utf-8 -iso-level 2 -J -R -o $@ -b boot/cadex.img image
	@rm -rf image

success:
	@echo "\nBuild finished. Type 'make run' to run"

clean:
	@rm -rf ${ISO_FILENAME} image
	@cd kernel && make clean
	@cd libc && make clean
	@cd usr && make clean
	@cd bin && make clean
	@cd apps && make clean

clear:
	@clear
