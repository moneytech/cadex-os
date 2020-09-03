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
				stdlib/strtod.o \
				objno.o \
				syscalls.o \
				syscall.o \
				string/string.o \
				stdio/stdio.o \
				malloc.o \
				math.o \
				qsort.o \
				scanf.o \
				assert.o \
				stdlib.o \
				toupper.o \
				tolower.o \
				wait.o \
				user-start.o \
				rand.o \
				stdlib/sudopasswd.o \
				alg/print_array.o \
				truegl/truegl.o \
				truegl/ui_button.o \
				truegl/ui_textbox.o \
				truegl/movable_scanf.o \
				truegl/ui_window.o \
				stdclib/cadex_version.o

all: baselib.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    libc/$<"

baselib.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating baselib.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
