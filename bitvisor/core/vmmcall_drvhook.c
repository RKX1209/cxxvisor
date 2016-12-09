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
  ulong drvaddr_v, drvaddr_p, size;
  ulong ret = 0;
  current->vmctl.read_general_reg(GENERAL_REG_RBX, &drvaddr_v);
  current->vmctl.read_general_reg(GENERAL_REG_RCX, &drvaddr_p);
  current->vmctl.read_general_reg(GENERAL_REG_RDX, &size);
  printf("k2e: driver has loaded at 0x%lx(0x%lx): size=%ul\n",
          drvaddr_v, drvaddr_p, size);
  current->vmctl.write_general_reg(GENERAL_REG_RAX, (ulong)ret);
}

static void
vmmcall_drvhook_init(void)
{
  vmmcall_register("drvhook", drvhook);
}
INITFUNC ("vmmcal0", vmmcall_drvhook_init);
