# The Cadex OS
[![Build Status](https://travis-ci.org/OpenCreeck/Cadex-OS-Official.svg?branch=master)](https://travis-ci.org/OpenCreeck/Cadex-OS-Official)

Cadex OS is a simple operating system kernel originally made by Prof. Douglas Thain at the University of Notre Dame and a variety of students including
Jack Mazanec, Douglas Smith, Ethan Williams, Jon Westhoff, and Kevin Wern. This is a fork of the repo https://github.com/dthain/basekernel

Cadex OS is _**not**_ a complete operating system, but it is a starting
point for those who wish to study and develop new operating system code.
If you want to build something _**different**_ than Windows, Linux, or MacOS,
Cadex OS may be a good place to try out your new ideas.

Cadex OS can boot an Intel PC-compatible virtual machine in 32-bit protected
mode, with support for VESA framebuffer graphics, ATA hard disks, ATAPI optical
devices, process management, memory protection, simple graphics, and basic filesystem.
From there, it's your job to write user-level programs and expand the system.

To be clear, this is raw low-level code, not a production system.
If you want to hack code and learn about operating system, you will like Cadex OS.
If you are looking for a new OS to run on your laptop, then this is not what you want.

This repo was made by HyperCreeck and actively maintained by HyperCreeck and people in this Organisation.

To learn more, see the [Cadex OS Wiki](https://github.com/opencreeck/Cadex-OS-Official/wiki).
 
## Quick Start Instructions

If you are building on a Linux-x86 machine
and have the QEMU virtual machine installed:

```
git clone https://github.com/opencreeck/Cadex-OS-Official
cd Cadex-OS-Official
make
qemu-system-i386 -cdrom cadex.iso
```

And you should see something like this:

<img src=screenshot.png align=center>

After some initial boot messages, you will see the kernel shell prompt.
This allows you to take some simple actions before running the first
user level program.  For example, read the boot messages to see
which atapi unit the cdrom is mounted on.  Then, use the `mount` command
to mount the cdrom filesystem on that unit:

<pre>
mount atapi 2 cdromfs
</pre>

Use the `list` command to examine the root directory:

<pre>
list /
</pre>

And use the `run` command to run a program:

<pre>
run /usr/bin/saver.exe
</pre>

## Cross-Compiling Instructions

If you are building on any other type of machine,
you will probably need to build a cross-compiler
using `./crosscompiler.sh` and then edit
`Makefile.config` to use the cross compiler binaries,
then execute `make` to create `cadex.iso`

