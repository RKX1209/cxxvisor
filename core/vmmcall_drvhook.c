#include "config.h"
#include "constants.h"
#include "current.h"
#include "debug.h"
#include "initfunc.h"
#include "panic.h"
#include "printf.h"
#include "process.h"
#include "thread.h"
#include "spinlock.h"
#include "vmmcall.h"

static void
drvhook(void)
{
  ulong driver_ip;
  ulong ret = 0;
  current->vmctl.read_ip(&driver_ip);
  printf("k2e: driver has loaded at 0x%lx", driver_ip);
  current->vmctl.write_general_reg(GENERAL_REG_RAX, (ulong)ret);
}

static void
vmmcall_drvhook_init(void)
{
  vmmcall_register("drvhook", drvhook);
}
INITFUNC ("vmmcal0", vmmcall_drvhook_init);
