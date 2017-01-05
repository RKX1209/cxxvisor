MAKE = make

.PHONY: all

all: bfc-make bfcxx-make bfcrt-make bfunwind-make libllvm-make

%-make:
	$(MAKE) -C $(BUILD_ABS)/makefiles/$*

.PHONY: clean
clean:
	#rm -r $(BUILD_ABS)/
	rm -r $(BUILD_ABS)/build_scripts
	rm -r $(BUILD_ABS)/makefiles
	rm -f $(BUILD_ABS)/env.sh
