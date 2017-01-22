# config macros
CONSTANTS-$(CONFIG_ENABLE_ASSERT) += -DENABLE_ASSERT
CONSTANTS-$(CONFIG_IDMAN) += -DIDMAN
CONSTANTS-$(CONFIG_VPN_PD) += -DVPN_PD

CFLAGS += -I$(k2e)/bitvisor/include/core -I$(k2e)/bitvisor/vpn/lib

objs-1 += kernel.o
asubdirs-1 += lib
