#!/bin/bash

system_map="System.map-`uname -r`"
address=`grep "R sys_call_table" /boot/${system_map} | cut -f1 -d' '`
if [ $? -ne 0 ]; then
  echo "Cannot fount ${system_map} on your /boot"
  exit -1
fi

sed -i "s/__SYSCALL_TABLE_ADDRESS__/0x${address}/" drvhook.c
