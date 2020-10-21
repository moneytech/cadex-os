include ../arch/i386/Makefile.config

KERNEL_OBJECTS=kernelcore.o \
			   scanf.o \
			   main.o \
			   utils.o \
			   console.o \
			   page.o \
			   keyboard.o \
			   mouse.o \
			   clock.o \
			   interrupt.o \
			   kmalloc.o \
			   pic.o \
			   ata.o \
			   cdromfs.o \
			   string.o \
			   bitmap.o \
			   graphics.o \
			   font.o \
			   syscall_handler.o \
			   process.o \
			   mutex.o \
			   list.o \
			   pagetable.o \
			   rtc.o \
			   kshell.o \
			   fs.o \
			   hash_set.o \
			   diskfs.o \
			   serial.o \
			   elf.o \
			   device.o \
			   kobject.o \
			   pipe.o \
			   bcache.o \
			   kprintf.o \
			   is_valid.o \
			   acpi.o \
			   module.o \
			   pci.o \
			   ide.o \
			   service.o \
			   cmos.o \
			   adlib.o \
			   sb16.o \
			   sse.o

cadex.img: alert bootblock kernel
	@cat bootblock kernel /dev/zero | head -c 1474560 > cadex.img

kernel: kernel.elf
	@${OBJCOPY} -O binary $< $@

bootblock: bootblock.elf
	@${OBJCOPY} -O binary $< $@

kernel.elf: ${KERNEL_OBJECTS}
	@${LD} ${KERNEL_LDFLAGS} -Ttext 0x10000 ${KERNEL_OBJECTS} -o $@

bootblock.elf: bootblock.o
	@${LD} ${KERNEL_LDFLAGS} -Ttext 0 $< -o $@

%.o: %.c
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo " CC    kernel/$<"

%.o: %.S
	@${CC} ${KERNEL_CCFLAGS} -I ../include $< -o $@
	@echo " AS    kernel/$<"

%.o: %.asm
	@nasm -f elf32 -O0 -o $@ $<
	@echo " NASM  kernel/$<"

alert:
	@echo "-- Building Kernel Sources..."

clean:
	@rm -rf cadex.img *.o *.elf kernel bootblock bootblock.o
