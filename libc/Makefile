include ../Makefile.config

LIBRARY_OBJECTS_CPP=cxxrt0.o

LIBRARY_OBJECTS=errno.o \
				ctype/_ctype.o \
				ctype/isalpha.o \
				ctype/isblank.o \
				ctype/isspace.o \
				ctype/isdigit.o \
				ctype/isascii.o \
				ctype/iscntrl.o \
				ctype/islower.o \
				ctype/isupper.o \
				ctype/isalnum.o \
				ctype/isprint.o \
				ctype/ispunct.o \
				ctype/isgraph.o \
				ctype/toupper.o \
				ctype/tolower.o \
				stdlib/abs.o \
				stdlib/atoi.o \
				stdlib/atof.o \
				stdlib/atol.o \
				stdlib/atoll.o \
				stdlib/bsearch.o \
				stdlib/qsort.o \
				stdlib/div.o \
				stdlib/fcvt.o \
				stdlib/ecvt.o \
				stdlib/labs.o \
				stdlib/ldiv.o \
				stdlib/lldiv.o \
				stdlib/llabs.o \
				stdlib/panic.o \
				stdlib/sudopasswd.o \
				stdlib/strtod.o \
				stdlib/cppdefs.o \
				stdlib/stdlib.o \
				string/index.o \
				string/bzero.o \
				string/explicit_bzero.o \
				string/swab.o \
				string/strverscmp.o \
				string/string.o \
				stdio/fopen.o \
				stdio/putchar.o \
				stdio/puts.o \
				unistd/chdir.o \
				unistd/close.o \
				unistd/read.o \
				objno.o \
				syscalls.o \
				syscall.o \
				stdio/stdio.o \
				malloc.o \
				math/math.o \
				qsort.o \
				scanf.o \
				assert.o \
				wait.o \
				crt0.o \
				rand.o \
				algorithm/print_array.o \
				truegl/truegl.o \
				truegl/ui_button.o \
				truegl/ui_textbox.o \
				truegl/movable_scanf.o \
				truegl/ui_window.o \
				sys/version.o \
				sys/contty.o \
				sul/base64_encode.o \
				sul/url_parser.o

all: alert baselib.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    libc/$<"

%.o: %.cpp
	@gcc -m32 -Wall -c -std=c++17 -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -I ../include -o $@ $<
	@echo "CPP    libc/$<"

baselib.a: ${LIBRARY_OBJECTS} ${LIBRARY_OBJECTS_CPP}
	@${AR} r $@ ${LIBRARY_OBJECTS} ${LIBRARY_OBJECTS_CPP}
	@echo "Creating library archive..."

alert:
	@echo "Building userspace libraries and libc..."

clean:
	@rm -rf *.a ./*/*.o *.o
