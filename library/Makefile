include ../Makefile.config

LIBRARY_OBJECTS=errno.o \
				ctype/_ctype.o \
				ctype/isalpha.o \
				ctype/isblank.o \
				stdlib/abs.o \
				stdlib/atol.o \
				stdlib/strtod.o \
				stdlib/atoll.o \
				stdlib/atof.o \
				stdlib/panic.o \
				stdlib/llabs.o \
				stdlib/div.o \
				stdlib/ldiv.o \
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
				truegl/ui_window.o

all: baselib.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    library/$<"

baselib.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating baselib.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
