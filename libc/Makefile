include ../arch/i386/Makefile.config

CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
LIBRARY_OBJECTS_CPP=crt/cxxrt0.o \
                    libcxx/LibGUI/StyleFormatter.o \
                    libcxx/LibGUI/CanvasBase.o \
		            libcxx/LibGUI/Canvas.o

LIBRARY_OBJECTS=crt/crti.o \
				$(CRTBEGIN_OBJ) \
				crt/crt0.o \
				crt/ubsan.o \
				ctype/_ctype.o \
				ctype/isalpha.o \
				ctype/isblank.o \
				ctype/isspace.o \
				ctype/isascii.o \
				ctype/isdigit.o \
				ctype/iscntrl.o \
				ctype/islower.o \
				ctype/isupper.o \
				ctype/isalnum.o \
				ctype/isprint.o \
				ctype/ispunct.o \
				ctype/isgraph.o \
				ctype/toupper.o \
				ctype/tolower.o \
				stdlib/errno.o \
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
				unistd/open.o \
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
				rand.o \
				util/print_array.o \
				libtgl/tgl_base.o \
				libtgl/ui_button.o \
				libtgl/ui_textbox.o \
				libtgl/movable_scanf.o \
				libtgl/ui_window.o \
				libtgl/compositor.o \
				libbmp/bitmap.o \
				libcur/curses.o \
				libcur/window.o \
				sys/version.o \
				sys/contty.o \
				sys/dbg_printf.o \
				sys/dlopen.o \
                printf/printf.o \
				sul/base64_encode.o \
				sul/url_parser.o \
				$(CRTEND_OBJ) \
				crt/crtn.o

all: alert baselib.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo " CC    libc/$<"

%.o: %.cpp
	@gcc -m32 -Wall -c -std=c++17 -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -fsanitize=undefined -I ../include -o $@ $<
	@echo " CXX    libc/$<"

baselib.a: ${LIBRARY_OBJECTS} ${LIBRARY_OBJECTS_CPP}
	@${AR} r $@ ${LIBRARY_OBJECTS} ${LIBRARY_OBJECTS_CPP}
	@echo "-- Creating library archive..."

alert:
	@echo "-- Building userspace libraries and libc..."

clean:
	@rm -rf *.a ./*/*.o *.o
