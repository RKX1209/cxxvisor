MAKE = make

.PHONY: all clean

all:
	$(MAKE) -C libs/makefiles
clean:
	$(MAKE) clean -C libs/makefiles
