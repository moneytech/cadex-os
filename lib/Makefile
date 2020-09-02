include ../Makefile.config

LIBRARY_OBJECTS=xserv_base.o \
				sysdrv.o

all: libstdcadex.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    lib/$<"

libstdcadex.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating libstdcadex.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
