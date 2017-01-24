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
#include "vt_ept.h"
#include <k2e/ModuleDescriptor.h>
#include <k2e/k2e_bitvisor.h>

static void
drvhook(void)
{
  ulong ret = 0;
  u32 area_num;
  u64 mod_area_v;
  u64 *mod_area_p;

  //struct ModuleDescriptor* md;
  //md = alloc(sizeof *md);
  // current->vmctl.read_general_reg(GENERAL_REG_RBX, &md->LoadVBase);
  // current->vmctl.read_general_reg(GENERAL_REG_RCX, &md->LoadPBase);
  // current->vmctl.read_general_reg(GENERAL_REG_RDX, &md->Size);

  current->vmctl.read_general_reg(GENERAL_REG_RBX, &mod_area_v);
  current->vmctl.read_general_reg(GENERAL_REG_RCX, &mod_area_p);
  current->vmctl.read_general_reg(GENERAL_REG_RDX, &area_num);

  /* Notify module loaded event to K2E */
  //k2e_on_module_load(g_k2e, md);
  /* Set hook points in module address range */
  //vt_ept_set_hook(mod_area_p, area_num);
  k2e_register_hook(mod_area_p, area_num, HOOK_TYPE_EXEC);

  current->vmctl.write_general_reg(GENERAL_REG_RAX, (ulong)ret);
}

static void
vmmcall_drvhook_init(void)
{
  vmmcall_register("drvhook", drvhook);
}
INITFUNC ("vmmcal0", vmmcall_drvhook_init);
