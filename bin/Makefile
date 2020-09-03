
include ../Makefile.config

USER_PROGRAMS= mkdiag.exe \
			   whoami.exe \
			   uname.exe \
			   bounce.exe \
			   clrscr.exe \
			   cat.exe \
			   cash.exe \
			   bshell.exe \
			   basic.exe \
			   sudo.exe \
			   text.exe \
			   dim.exe \
			   ccexample.exe

all: $(USER_PROGRAMS)

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC     bin/$<"

%.o: %.cc
	@gcc ${KERNEL_CPPFLAGS} -I ../include $< -o $@
	@echo "CPP     bin/$<"

%.exe: %.o ../libc/user-start.o ../libc/baselib.a
	@${LD} ${KERNEL_LDFLAGS} -melf_i386 -Ttext 0x80000000 ../libc/user-start.o $< ../libc/baselib.a -o $@

clean:
	@rm -rf *.exe *.o
