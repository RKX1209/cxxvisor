K2ESRC := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
MAKE = make
all: all-release
all-release: bitvisor-release-make
bitvisor-release-make: libs-release-make
	$(MAKE)	-C $(K2ESRC)/bitvisor
libs-release-make: libs-release-config
libs-release-config:
	./configure.sh --compiler g++
.PHONY config: libs-release-config
