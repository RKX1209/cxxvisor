MAKE = make

.PHONY: all

all: bfc-make bfcxx-make bfcrt-make

%-make:
	$(MAKE) -C $(BUILD_ABS)/makefiles/$*

.PHONY: clean
clean:
	#rm -r libs/
	rm -r libs/build_scripts
	rm -r libs/makefiles
	rm -f libs/env.sh
