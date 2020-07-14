
include ../Makefile.config

USER_PROGRAMS=ball.exe clock.exe clrscr.exe splash.exe color.exe copy.exe tedit.exe livestat.exe manager.exe fractal.exe procstat.exe saver.exe sh.exe snake.exe sysstat.exe ub_ubasic.exe

all: $(USER_PROGRAMS)

%.o: %.c
	${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@

%.exe: %.o ../library/user-start.o ../library/baselib.a
	${LD} ${KERNEL_LDFLAGS} -Ttext 0x80000000 ../library/user-start.o $< ../library/baselib.a -o $@

clean:
	rm -rf *.exe *.o
