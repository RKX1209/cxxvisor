#include <k2e/MemHook.hpp>
#include <k2e/Utils.h>
extern "C" {
#include <core/printf.h>
}
#define PAGESIZE 4096

namespace k2e {

HookList *MemHookInfo::s_hooks = new HookList();
HookArea *MemHookInfo::s_hooked_area = new HookArea();

void register_hook(class MemHookInfo* hook, HookType hook_type) {
  /* XXX: must use std::map instead std::set. */
  uint64_t *mod_area = hook->m_module_areas;
  HookArea *hooked_area = MemHookInfo::get_hooked_area();
  HookList *hooks = MemHookInfo::get_hook_list();

  printf("mod_area=%p, hooked_area=%p, hooks=%p\n", reinterpret_cast<void *>(mod_area),
                                                    reinterpret_cast<void *>(hooked_area),
                                                    reinterpret_cast<void *>(hooks));
  for (int i = 0; i < hook->m_area_num; i++) {
    printf("searching hook handler in 0x%llx\n", mod_area[i]);
    HookedPage hp(mod_area[i], 0);
    auto it = hooked_area->find(hp);
    if (it != hooked_area->end()) {
      printf("already exist\n");
      /* address already exist. So update attribute (nxor) */
      it->set_hooktype(~(it->get_hooktype() ^ hook_type));
    } else {
      printf("not exist- insert new one\n");
      /* Puts hook points */
      hooked_area->insert(HookedPage(mod_area[i], hook_type));
    }
  }
  hooks->push_back(hook);

}

extern "C" {
void k2e_register_hook_internal(uint64_t* mod_area, uint32_t area_num, uint8_t hook_type) {
  printf("k2e_register_hook_internal\n");
  // MemHookInfo *hook_info = new MemHookInfo(mod_area, area_num, hook_type);
  // if (hook_info)
  //   register_hook(hook_info, hook_type);
}

uint8_t k2e_get_hooktype(uint64_t addr) {
  HookArea *hooked_area = MemHookInfo::get_hooked_area();
  HookedPage hp(addr, 0);
  //HookArea::iterator it = hooked_area->lower_bound(hp);

  // if (it != hooked_area->end() && addr <= (*it).get_address() + PAGESIZE) {
  //   /* addr is in range [hooked_ent, hooked_ent+PAGESIZE] */
  //   return (*it).get_hooktype();
  // }

  return ~0;
}

uint8_t k2e_is_hooked(uint64_t addr, uint8_t hook_type) {
  return (uint8_t)~(k2e_get_hooktype(addr) | hook_type);
}

}

}
