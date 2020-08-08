# Cadex OS Build Makefile for i386 architecture.
include Makefile.config

LIBRARY_SOURCES=$(wildcard library/*.c)
LIBRARY_HEADERS=$(wildcard library/*.h)
USER_SOURCES=$(wildcard usr/*.c)
SYSTEM_BIN_SOURCES=$(wildcard bin/*.c)
USER_PROGRAMS=$(USER_SOURCES:c=exe)
SYSTEM_BIN_FILES=$(SYSTEM_BIN_SOURCES:c=exe)
KERNEL_SOURCES=$(wildcard kernel/*.[chS])

.PHONY: clean

all: clear clean cadex.iso success # run # Uncomment this run command to run the OS after you've built the OS

run: cadex.iso # hddimg
					#  | This .exe is for compatibility for WSL. See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
		    		# \/ This is ignored if you are not building on a WSL.
	qemu-system-i386.exe -cdrom cadex.iso -hda disk.img -device isa-debug-exit,iobase=0xf4,iosize=0x04 || qemu-system-i386 -cdrom cadex.iso -hda disk.img -device isa-debug-exit,iobase=0xf4,iosize=0x04

debug: cadex.iso hddimg
					#  | This .exe is for compatibility for WSL. See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
		    		# \/ This is ignored if you are not building on a WSL.
	qemu-system-i386.exe -cdrom cadex.iso -hda disk.img -s -S -device isa-debug-exit,iobase=0xf4,iosize=0x04 & || qemu-system-i386 -cdrom cadex.iso -hda disk.img -s -S  &

hddimg:
			#  | This .exe is for compatibility for WSL. See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
		    # \/ This is ignored if you are not building on a WSL.
	qemu-img.exe create disk.img 10M || qemu-img create disk.img 10M

library/baselib.a: $(LIBRARY_SOURCES) $(LIBRARY_HEADERS)
	cd library && make

$(USER_PROGRAMS): $(USER_SOURCES) library/baselib.a $(LIBRARY_HEADERS)
	cd usr && make

$(SYSTEM_BIN_FILES): $(SYSTEM_BIN_SOURCES) library/baselib.a $(LIBRARY_HEADERS)
	cd bin && make

kernel/cadex.img: $(KERNEL_SOURCES) $(LIBRARY_HEADERS)
	cd kernel && make

image: kernel/cadex.img $(USER_PROGRAMS) $(SYSTEM_BIN_FILES)
	rm -rf image
	mkdir image image/boot image/usr image/data image/usr/bin image/bin image/sys
	cp kernel/cadex.img image/boot
	cp usr/kevin.txt image/usr/share
	cp sys/sys.json image/sys/
	cp $(USER_PROGRAMS) image/usr/bin
	cp $(SYSTEM_BIN_FILES) image/bin
	head -2000 /usr/share/dict/words > image/data/words

cadex.iso: image
	${ISOGEN} -input-charset utf-8 -iso-level 2 -J -R -o $@ -b boot/cadex.img image
success:
	@echo "----------------------------------------------------"
	@echo "Successfully compiled kernel. Type 'make run' to run"
	@echo "----------------------------------------------------"
clean:
	rm -rf cadex.iso image
	cd kernel && make clean
	cd library && make clean
	cd usr && make clean

clear:
	clear || cls
