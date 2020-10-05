# Build instructions for Cadex OS
#### Installing the toolchain

For building Cadex OS, you need to install the toolchain.
Building toolchain from source is recommended, but prebuilt binaries are available.

- If you are building toolchain from source, visit [this]http://cadex-os-wiki.rf.gd/Toolchain#Building) wiki
- If you don't wish to build the toolchain from source (not recommended), you can download prebuilt binaies for ubuntu from [here](https://hypercreeck.cf/cadex/os/toolchain.php)

#### Building the OS

If you are building on a Linux-x86 machine
and have the QEMU installed, run:

```bash
# Clone the repo
git clone https://github.com/opencreeck/Cadex-OS-Official
# Enter the source directory
cd Cadex-OS-Official
# Build the source
make
# Run the built ISO image. (Remove the .exe in the qemu-system-i386 in the Makefile)
make run
```

And you should see something like this:

<img src=img/screenshot.png align=center>

After some initial boot messages, you will see the kshell prompt.
This allows you to take some simple actions before running the first
user-level program. For example, read the boot messages to see
which atapi unit the cdrom is mounted on. Then, use the `mount` command
to mount the cdrom filesystem on that unit:

```bash
mount atapi <unit> cdromfs
```

Use the `ls` command to list the root directory:

```bash
ls /
```

And use the `./` prefix to run a program (For example, a simple screensaver):

```bash
./usr/bin/saver.exe
```
