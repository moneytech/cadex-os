include ../Makefile.config

LIBRARY_OBJECTS=errno.o \
				_ctype.o \
				objno.o \
				syscalls.o \
				syscall.o \
				string.o \
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
				algorithm/print_array.o \
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
