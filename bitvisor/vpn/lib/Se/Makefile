# config macros
CONSTANTS-$(CONFIG_ENABLE_ASSERT) += -DENABLE_ASSERT
CONSTANTS-$(CONFIG_IDMAN) += -DIDMAN
CONSTANTS-$(CONFIG_VPN_PD) += -DVPN_PD

CFLAGS += -I$(k2e)/bitvisor/crypto -I$(k2e)/bitvisor/crypto/openssl-$(OPENSSL_VERSION)/include -I$(k2e)/bitvisor/vpn/lib

objs-1 += SeConfig.o SeCrypto.o SeIke.o SeInterface.o SeIp4.o SeIp6.o
objs-1 += SeKernel.o SeMemory.o SePacket.o SeSec.o SeStr.o SeVpn.o
objs-1 += SeVpn4.o SeVpn6.o
