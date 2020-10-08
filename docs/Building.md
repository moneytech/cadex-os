# Building Cadex OS

#### Installing the toolchain

For building Cadex OS, you need to install the toolchain.
Building toolchain from source is recommended, but prebuilt binaries are available.

- If you are building toolchain from source, visit (this)[http://cadex-os-wiki.rf.gd/Toolchain#Building] site
- If you don't wish to build the toolchain from source (not recommended), you can download prebuilt binaies for ubuntu from (here)[https://hypercreeck.cf/cadex/os/toolchain.php]

#### Building the OS

If you are building on a Linux-x86 machine
and have the QEMU installed, run:

```bash
# Clone the repo
git clone https://github.com/opencreeck/cadex-os-official
# Enter the source directory
cd Cadex-OS-Official
# Build the source
make
# Run the built ISO image. (Remove the .exe in the qemu-system-i386 in the Makefile)
make run
```
