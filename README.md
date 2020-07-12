# Cadex OS
[![Travis CI Build Status](https://travis-ci.org/OpenCreeck/Cadex-OS-Official.svg?branch=master)](https://travis-ci.org/OpenCreeck/Cadex-OS-Official)

Cadex OS is a simple operating system kernel originally made by Prof. Douglas Thain at the University of Notre Dame and a variety of students including
Jack Mazanec, Douglas Smith, Ethan Williams, Jon Westhoff, and Kevin Wern. And now maintained by HyperCreeck. This is a fork of the repo https://github.com/dthain/basekernel

If you want to build apps for something _**different**_ than Windows, Linux, or MacOS,
Cadex OS may be a good place to try out your new ideas. Cadex OS has all the libraries and APIs to create your own app.

Cadex OS can boot an Intel PC-compatible virtual machine in 32-bit protected
mode, with support for VESA framebuffer graphics, ATA hard disks, ATAPI optical
devices, process management, memory protection, simple graphics, and basic filesystem.
From there, it's your job to write user-level programs and expand the system.

This repo was made by HyperCreeck and actively maintained by HyperCreeck and people in this Organisation.

To learn more, see the __[Cadex OS Wiki](https://github.com/opencreeck/Cadex-OS-Official/wiki).__
 
## Quick Start Instructions

#### Installing the toolchain

For building Cadex OS, you need to install the toolchain. 
Building toolchain from source is recommended, but prebuilt binaries are available.
 - If you are building toolcahin from source, visit [this](https://hypercreeck.cf/cadex/os/toolchain.php) site
 - If you don't wish to build the toolchain from source (not recommended), you can download prebuilt binaies for ubuntu from [here](https://hypercreeck.cf/cadex/os/toolchain.php)
 
#### Building the OS

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

And use the `run` command to run a program (for example, a simple screensaver):

<pre>
run /usr/bin/saver.exe
</pre>

## Cross-Compiling Instructions

If you are building on any other type of machine,
you will probably need to build a cross-compiler
using `./crosscompiler.sh` and then edit
`Makefile.config` to use the cross compiler binaries,
then execute `make` to create `cadex.iso`

