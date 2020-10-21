
include ../arch/i386/Makefile.config

USER_PROGRAMS=ball.exe \
			  bfk.exe \
			  brainkick.exe \
			  clock.exe \
			  color.exe \
			  copy.exe \
			  fractal.exe \
			  livestat.exe \
			  manager.exe \
			  matrix.exe \
			  procstat.exe \
			  saver.exe \
			  snake.exe \
			  splash.exe \
			  sysstat.exe \
			  tedit.exe

all: alert $(USER_PROGRAMS)

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo " CC     usr.bin/$<"

%.exe: %.o ../libc/crt/crt0.o ../libc/baselib.a
	@${LD} ${KERNEL_LDFLAGS} -Ttext 0x80000000 ../libc/crt/crt0.o $< ../libc/baselib.a -o $@

alert:
	@echo "-- Building userspace user programs (/usr/bin)..."

clean:
	@rm -rf *.exe *.o
