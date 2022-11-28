#!/bin/bash

set -xe

uname -a

cd /btrfs-progs

./mkfs.btrfs -fK /dev/vdb

mount /dev/vdb /mnt

./btrfs sub show /mnt
./btrfs sub create /mnt/sub
./btrfs sub snap /mnt/sub /mnt/snap

./btrfs sub show /mnt/sub
./btrfs sub show /mnt/snap
