include ../Makefile.config

LIBRARY_OBJECTS=errno.o \
				_ctype.o \
				objno.o \
				syscalls.o \
				syscall.o \
				string.o \
				stdio.o \
				malloc.o \
				math.o \
				qsort.o \
				scanf.o \
				assert.o \
				stdlib.o \
				toupper.o \
				tolower.o \
				wait.o \
				stdlib/sudopasswd.o \
				algorithm/print_array.o \
				truegl/truegl.o \
				truegl/ui_button.o

all: user-start.o baselib.a rand.o

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "[BUILD] library/$<"

baselib.a: ${LIBRARY_OBJECTS}
	@${AR} rv $@ ${LIBRARY_OBJECTS}
	@echo "[BUILD] Creating baselib.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
