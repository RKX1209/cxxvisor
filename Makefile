K2ESRC := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
MAKE = make
all: all-release
all-release: bitvisor-release-make
bitvisor-release-make:
	$(MAKE)	-C $(K2ESRC)/bitvisor
