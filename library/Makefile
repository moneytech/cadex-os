include ../Makefile.config

LIBRARY_OBJECTS=errno.o objno.o syscall.o syscalls.o string.o stdio.o malloc.o math.o qsort.o scanf.o gwin.o assert.o _ctype.o toupper.o tolower.o wait.o

all: user-start.o baselib.a rand.o

%.o: %.c
	${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@

baselib.a: ${LIBRARY_OBJECTS}
	${AR} rv $@ ${LIBRARY_OBJECTS}

clean:
	rm -rf *.a *.o
