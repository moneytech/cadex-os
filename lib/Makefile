include ../Makefile.config

LIBRARY_OBJECTS=

all: libdev_drivers.a

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo "CC    lib/$<"

libdev_drivers.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating libdev_drivers.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
