CONSTANTS-$(CONFIG_ENABLE_ASSERT) += -DENABLE_ASSERT
CONSTANTS-$(CONFIG_STORAGE_PD) += -DSTORAGE_PD
CONSTANTS-$(CONFIG_ENABLE_ASSERT) += -DENABLE_ASSERT
CONSTANTS-$(CONFIG_SELECT_AES_GLADMAN) += -DAES_GLADMAN

CFLAGS += -I$(k2e)/bitvisor/crypto -I$(k2e)/bitvisor/crypto/openssl-$(OPENSSL_VERSION)/include

objs-1 += aes_xts.o crypto.o none.o
