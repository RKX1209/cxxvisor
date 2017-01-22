CONSTANTS-$(CONFIG_ENABLE_ASSERT) += -DENABLE_ASSERT
CONSTANTS-$(CONFIG_IDMAN_PD) += -DIDMAN_PD
CONSTANTS-1 += -DNTTCOM

CFLAGS += -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/ccid -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/iccard -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/idman_pkcs11
CFLAGS += -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/pcsc -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/pkcs11 -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/standardio
CFLAGS += -I$(k2e)/bitvisor/$(k2e)/bitvisor/$(k2e)/bitvisor/idman/lib/user

objs-1 += IDMan_IPCommon.o IDMan_IPgenerateSignature.o
objs-1 += IDMan_IPgetCertificate.o IDMan_IPgetStaticPassword.o
objs-1 += IDMan_IPuserAuthPKCS11.o IDMan_IPverifySignature.o
