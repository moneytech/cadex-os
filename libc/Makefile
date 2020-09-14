include ../Makefile.config

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
				string/index.o \
				string/bzero.o \
				string/explicit_bzero.o \
				string/swab.o \
				string/strverscmp.o \
				string/string.o \
				objno.o \
				syscalls.o \
				syscall.o \
				stdio/stdio.o \
				malloc.o \
				math/math.o \
				qsort.o \
				scanf.o \
				assert.o \
				stdlib.o \
				toupper.o \
				tolower.o \
				wait.o \
				crt0.o \
				rand.o \
				algorithm/print_array.o \
				truegl/truegl.o \
				truegl/ui_button.o \
				truegl/ui_textbox.o \
				truegl/movable_scanf.o \
				truegl/ui_window.o \
				cadex/cadex_version.o \
				cadex/contty.o \
				sul/base64_encode.o

all: baselib.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    libc/$<"

baselib.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating baselib.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
