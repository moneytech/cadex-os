
include ../Makefile.config

USER_PROGRAMS=ball.exe clock.exe splash.exe color.exe copy.exe tedit.exe livestat.exe manager.exe fractal.exe procstat.exe saver.exe snake.exe sysstat.exe matrix.exe
all: $(USER_PROGRAMS)

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC     usr/$<"

%.exe: %.o ../libc/crt0.o ../libc/baselib.a
	@${LD} ${KERNEL_LDFLAGS} -Ttext 0x80000000 ../libc/crt0.o $< ../libc/baselib.a -o $@

clean:
	@rm -rf *.exe *.o
