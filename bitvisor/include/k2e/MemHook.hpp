#ifndef MEM_HOOK_HPP
#define MEM_HOOK_HPP

#include <limits.h>
#include <vector>
#include <set>
#include <stdint.h>

namespace k2e {

typedef uint8_t HookType;

class HookedPage {
private:
  uint64_t m_address;
  mutable HookType m_hook_type;
public:
  HookedPage(uint64_t address, HookType hook_type): m_address(address), m_hook_type(hook_type) {}
  bool operator<(const HookedPage &hp) const { return m_address < hp.get_address(); }
  uint64_t get_address() const { return m_address; }
  HookType get_hooktype() const { return m_hook_type; }
  void set_hooktype(HookType type) const { m_hook_type = type; }
};

class MemHookInfo;

typedef std::set<HookedPage> HookArea;
typedef std::vector<MemHookInfo *> HookList;

class MemHookInfo {
private:

  uint64_t *m_module_areas;
  uint32_t m_area_num;
  HookType m_hook_type;

  static HookArea *s_hooked_area;
  static HookList *s_hooks;
public:
  MemHookInfo(): m_module_areas(NULL), m_area_num(0) {}
  MemHookInfo(uint64_t *module_areas, uint32_t area_num, HookType hook_type): m_module_areas(module_areas), m_area_num(area_num), m_hook_type(hook_type) {}

  HookType get_hooktype() const { return m_hook_type; }
  static HookArea *get_hooked_area() { return s_hooked_area; }
  static HookList *get_hook_list() { return s_hooks; }
  friend void register_hook(class MemHookInfo*, HookType);
};

}

#endif
