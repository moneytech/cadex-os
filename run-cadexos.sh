#!/bin/bash

# Bash script to create a disk file and run the Cadex OS
qemu-img create -f qcow2 disk.img 1G
qemu-system-i386 -cdrom cadexos-v0.1.5-release.iso -m size=500M -drive 'file=disk.img,format=qcow2' -device isa-debug-exit,iobase=0xf3,iosize=0x04 