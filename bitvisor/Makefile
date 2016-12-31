DIR ?= .
V ?= 0
include Makefile.common

.PHONY : all
all : build-all

.PHONY : clean
clean : clean-all

NAME   = k2e
FORMAT = elf32-i386
elf    = $(NAME).elf
map    = $(NAME).map
lds    = $(NAME).lds
target = $(elf)

subdirs-1 += core drivers
subdirs-$(CONFIG_STORAGE) += storage
subdirs-$(CONFIG_VPN) += vpn
subdirs-$(CONFIG_IDMAN) += idman
subdirs-1 += net
subdirs-$(CONFIG_IP) += ip
asubdirs-$(CONFIG_CRYPTO) += crypto
psubdirs-1 += process
subdirs-1 += k2e

process-depends-$(CONFIG_CRYPTO) += $(dir)crypto/$(outa_p)
process-depends-$(CONFIG_IDMAN) += $(dir)idman/$(outo_p)
process-depends-$(CONFIG_STORAGE) += $(dir)storage/$(outo_p)
process-depends-$(CONFIG_VPN) += $(dir)vpn/$(outo_p)


$(dir)$(elf) : $(defouto) $(dir)$(lds)
	$(V-info) LD $(dir)$(elf)
	$(CC) $(LDFLAGS) -L../libs/makefiles/bfcrt/bin/cross/ -L../libs/makefiles/bfunwind/bin/cross/ -L../libs/sysroot/x86_64-elf/lib/ \
		-Wl,-T,$(dir)$(lds) -Wl,--cref \
		-Wl,-Map,$(dir)$(map) -o $(dir)$(elf) $(defouto) \
		-static -lbfcrt_static -lbfunwind_static -lc++abi -Wl,-u__errno -lc -lbfc -lc++
	$(OBJCOPY) --output-format $(FORMAT) $(dir)$(elf)

.PHONY : build-all
build-all : $(CONFIG) defconfig
	case "`$(SED) 1q $(DIR)/$(depends) 2>/dev/null`" in \
	''): >> $(DIR)/$(depends);; esac
	$(MAKE) $(V-makeopt-$(V)) -f Makefile.build build-dir DIR=$(DIR) V=$(V)
	$(SIZE) $(dir)$(elf)

.PHONY : clean-all
clean-all :
	$(MAKE) $(V-makeopt-$(V)) -f Makefile.clean clean-dir DIR=$(DIR) V=$(V)

.PHONY : config
config : $(CONFIG)
	$(MAKE) -f Makefile.config config

$(CONFIG) : Makefile.config
	: >> $(CONFIG)
	$(MAKE) -f Makefile.config update-config

defconfig :
	cp defconfig.tmpl defconfig

$(dir)process/$(outp_p) : $(process-depends-1)
