include ../Makefile.config

LIBRARY_OBJECTS=WindowCompositor.o\
				widgets/Button.o \
				widgets/WidgetBase.o \
				io/ostream.o \
				io/istream.o \
				io/iostream.o

all: stdcpplib.a

%.o: %.cpp
	@${CPP} -m32 -Wall -c -ffreestanding -nostdlib -nodefaultlibs -fno-pie -fno-builtin -fno-use-cxa-atexit -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fpermissive -g -I ../include -o $@ $<
	@echo "CPP    lib/$<"

stdcpplib.a: ${LIBRARY_OBJECTS}
	@${AR} r $@ ${LIBRARY_OBJECTS}
	@echo "Creating stdcpplib.a..."

clean:
	@rm -rf *.a ./*/*.o *.o
