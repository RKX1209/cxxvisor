MAKE = make

.PHONY: all clean
all:
	$(MAKE) -C libs/makefiles
	$(MAKE) -C bitvisor/boot/loader
	$(MAKE) -C bitvisor/boot/uefi-loader
	$(MAKE) -j8 -C bitvisor
clean:
	$(MAKE) clean -C libs/makefiles
	$(MAKE) clean -C bitvisor
