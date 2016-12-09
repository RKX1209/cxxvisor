KERNDIR := /lib/modules/`uname -r`/build
BUILD_DIR := $(shell pwd)

RM			= rm -f

obj-m 				:= drvhook.o
smallmod-objs := drvhook.o

.PHONY : all
all : drvhook

.PHONY : clean
clean :
	$(RM) drvhook
	$(RM) *.o
	$(RM) *.ko

drvhook : drvhook.c
	sudo bash set_syscall_table_address.sh
	make -C $(KERNDIR) SUBDIRS=$(BUILD_DIR) KBUILD_VERBOSE=$(VERBOSE) modules
