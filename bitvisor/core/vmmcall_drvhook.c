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
#include "mm.h"
#include <k2e/ModuleDescriptor.h>
#include <k2e/k2e_bitvisor.h>

static void
drvhook(void)
{
  ulong ret;
  struct ModuleDescriptor* md;
  md = alloc(sizeof *md);
  current->vmctl.read_general_reg(GENERAL_REG_RBX, &md->LoadVBase);
  current->vmctl.read_general_reg(GENERAL_REG_RCX, &md->LoadPBase);
  current->vmctl.read_general_reg(GENERAL_REG_RDX, &md->Size);
  // printf("k2e: driver has loaded at 0x%lx(0x%lx): size=%ul\n",
  //         drvaddr_v, drvaddr_p, size);
  k2e_on_module_load(g_k2e, md);
  current->vmctl.write_general_reg(GENERAL_REG_RAX, (ulong)ret);
}

static void
vmmcall_drvhook_init(void)
{
  vmmcall_register("drvhook", drvhook);
}
INITFUNC ("vmmcal0", vmmcall_drvhook_init);
