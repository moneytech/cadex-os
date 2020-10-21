# Cadex OS

[![Build Status](https://travis-ci.org/CadexOS/Cadex-OS-Official.svg?branch=master)](https://travis-ci.org/CadexOS/Cadex-OS-Official)

Cadex OS is a 32-bit UNIX- operating system.

Cadex OS is a free and open-source project. You can fork this project and make your own OS from this.
Cadex OS is UNIX-compatible, except that Cadex OS doesn't support VFS (Virtual filesystem) and some UNIX libraries are not implemented.

Cadex OS can boot an Intel PC-compatible virtual machine in 32-bit protected
mode, with support for VESA framebuffer graphics, ATA hard disks, ATAPI optical
devices, process management, memory protection, small graphics, a standard libc, C++ language support and basic filesystem (DFS). Cadex OS supports ELF executables, therefore apps are also supported

## Some useful info about Cadex OS

- Cadex OS supports a small subset of libc, and more functions and libraries from libc need to be implemented.
- Cadex OS has a small BASIC interpreter that can be used to write small programs.
- Cadex OS supports graphical and text-based applications
- Cadex OS uses ELF as the binary format
- Cadex OS supports modules, but it is still in development and is not in the Makefile
- Cadex OS will be useful if you are a beginner in C programming language and you want to write small programs.
- Cadex OS has a small graphics library called TrueGL. TrueGL is also a UI library
- Cadex OS has many useful string functions defined at `library/string.c`
- Cadex OS uses some code from Musl libc for the libc in Cadex OS. Libraries that are from Musl libc should contain a license header on the top.
- Cadex OS supports C++ apps and thus it has a C++ library. The C++ library is implemented as a header-only library (Note that the C++ library used in this project is completely written from scratch and thus it may not be complaint to the C++ standards)
- Cadex OS is targeted on x86 systems and if you want it to run on ARM-based systems, you will need to rewrite the bootloader and some kernel-side code

To learn more, see the [Cadex OS Wiki](http://cadex-os-wiki.rf.gd).

## Features

- VESA Framebuffer Graphics driver
- ATA driver
- ATAPI driver
- AdLib sound card driver
- ACPI driver
- PCI driver
- PS/2 Mouse driver
- IDE driver
- 8x8 font (modified version of Pearl font from Linux sources)
- Memory Protection
- Standard libc and libcxx
- Support for making apps with C++
- Basic process management
- Basic filesystem (DiskFS, aka DFS)
- Basic bootloader
- Support for ELF executables
- Basic graphics library (TrueGL)
- Non-UNIX syscalls
- Support for process piping
- A shell implemented in the kernel side: KShell
- Some basic games like Snake

## Notable components

- **kshell**: A small but efficient shell implemented on the kernel space
- **DiM**: A very small text editor
- **pam**: A package manager for Cadex OS (not implemented)
- **cash**: A small bash-like shell implemented on the userspace

## Project structure

- **apps**: Sources for C++ apps
- **arch**: `Makefile.config` for i386 architecture
- **basefs**: Base filesystem folder that goes into the ISO image
- **bin**: System/user commands (`/bin`)
- **docs**: Documentation about used drivers and APIs
- **doxygen**: Config files for Doxygen
- **include**: Header files for C and C++ libraries
- **kernel**: The core kernel source
- **libc**: Source files for libc and libcxx (This includes the standard system libraries)
- **scripts**: Scripts for generating ramfs image and other purposes
- **usr.bin**: User commands (`/usr/bin`)

## Building

First, do the steps mentioned in [docs/Building.md](docs/Building.md).

After you've built Cadex OS, run `make run` and you should see Cadex OS QEMU.

<img src=docs/img/screenshot.png align=center>

After some initial boot messages, you will see the kshell prompt.
This allows you to take some simple actions before running the first
user-level program. For example, read the boot messages in the qemu serial console to see
which atapi unit the cdrom is mounted on. Then, use the `mount` command
to mount the cdrom filesystem on that unit:

```bash
mount atapi <unit> cdromfs
```

Use the `ls` command to examine the root directory:

```bash
ls /
```

And use the `./` prefix to run a program (For example, a simple screensaver):

```bash
./usr/bin/saver.exe
```

## Discord

We have a Discord server! Everyone is welcome to the server! Join the server from
[this invite link](https://discord.gg/mF9gG5W)

<!-- # Cross-Compiling Instructions

If you are building on any other type of machine (i.e, on WSL or any non-linux machine),
you will probably need to build a cross-compiler
using `./scripts/build-toolchain.sh` and then edit
`Makefile.config` to use the cross compiler binaries,
then execute `make` to create `cadex.iso` -->

## Contributing

See [CONTRIBUTING.md](docs/CONTRIBUTING.md)
