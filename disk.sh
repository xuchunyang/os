#!/bin/bash
#
# This scripts creates a GRUB CD-ROM disk image.
#
# Base on https://github.com/xuchunyang/Basic_OS/blob/master/disk.sh
#

rm -v -rf isofiles

echo 'Creating isofiles'
mkdir -v isofiles || exit 1

echo 'Creating directories'
mkdir -v -p isofiles/boot/grub || exit 1

echo 'Copying the files'
cp -v grub.cfg isofiles/boot/grub || exit 1
cp -v kernel.bin isofiles/boot || exit 1

echo 'Creating a CD-ROM from isofiles'
grub-mkrescue --output=myos.iso isofiles || exit 1
