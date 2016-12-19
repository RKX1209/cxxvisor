#!/bin/sh
ssh root@$1 << EOF
insmod /home/rkx/Programming/OSS/k2e/bitvisor/tools/drvhook/drvhook.ko target="testmod"
insmod /home/rkx/test_mod/testmod.ko
dmesg | tail
EOF
# cd /home/rkx/test_mod/;./client
# dmesg | tail


