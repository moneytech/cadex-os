include Makefile.config

LIBRARY_SOURCES=$(wildcard library/*.c)
LIBRARY_HEADERS=$(wildcard library/*.h)
USER_SOURCES=$(wildcard usr/*.c)
USER_PROGRAMS=$(USER_SOURCES:c=exe)
KERNEL_SOURCES=$(wildcard kernel/*.[chS])

all: clean cadex.iso run

run: cadex.iso # hddimg
					#  | This .exe is for compatibility for WSL. See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
		    		# \/ This is ignored if you are not building on a WSL.
	qemu-system-i386.exe -cdrom cadex.iso -hda disk.img || qemu-system-i386 -cdrom cadex.iso -hda disk.img

debug: cadex.iso hddimg
					#  | This .exe is for compatibility for WSL. See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
		    		# \/ This is ignored if you are not building on a WSL.
	qemu-system-i386.exe -cdrom cadex.iso -hda disk.img -s -S & || qemu-system-i386 -cdrom cadex.iso -hda disk.img -s -S &

hddimg:
			#  | This .exe is for compatibility for WSL. See https://github.com/opencreeck/Cadex-OS-Official/wiki/WSLCompat
		    # \/ This is ignored if you are not building on a WSL.
	qemu-img.exe create disk.img 10M || qemu-img.exe create disk.img 10M

library/baselib.a: $(LIBRARY_SOURCES) $(LIBRARY_HEADERS)
	cd library && make

$(USER_PROGRAMS): $(USER_SOURCES) library/baselib.a $(LIBRARY_HEADERS)
	cd usr && make

kernel/cadex.img: $(KERNEL_SOURCES) $(LIBRARY_HEADERS)
	cd kernel && make

image: kernel/cadex.img $(USER_PROGRAMS)
	rm -rf image
	mkdir image image/boot image/usr image/data image/usr/bin
	cp kernel/cadex.img image/boot
	cp $(USER_PROGRAMS) image/usr/bin
	head -2000 /usr/share/dict/words > image/data/words

cadex.iso: image
	${ISOGEN} -input-charset utf-8 -iso-level 2 -J -R -o $@ -b boot/cadex.img image

clean:
	rm -rf cadex.iso image
	cd kernel && make clean
	cd library && make clean
	cd usr && make clean
