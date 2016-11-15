#!/bin/sh
ELF=orthros.elf
DEV=/dev/nbd0
DEV0=/dev/nbd0p1
MNT=/mnt
qemu-nbd $1 --connect=$DEV
mount $DEV0 $MNT
cp $ELF $MNT/boot/
umount $MNT
qemu-nbd --disconnect $DEV

