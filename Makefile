K2ESRC := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
MAKE = make

.PHONY: all all-release bitvisor-make libs-release-make

all: all-release
all-release: bitvisor-make libs-release-make

libs-release-make: bfc-make bfcxx-make #libs-release-config

libs-release-config:
	./configure

%-make:
	$(MAKE) -C $(K2ESRC)$*

.PHONY: clean
clean:
	#rm -r libs/
	rm -r libs/build_scripts
	rm -f libs/env.sh
	rm -f Makefile.common
#########
# bfcxx #
#########
