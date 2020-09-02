include ../Makefile.config

LIBRARY_OBJECTS=xserv_base.o \
				sysdrv.o

all: lib_cadex_base.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    lib/$<"

lib_cadex_base.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating lib_cadex_base.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
