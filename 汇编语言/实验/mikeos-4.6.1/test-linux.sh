#!/bin/sh

# This script starts the QEMU PC emulator, booting from the
# MikeOS floppy disk image

qemu-system-i386 -soundhw pcspk -drive format=raw,file=disk_images/mikeos.flp,index=0,if=floppy
