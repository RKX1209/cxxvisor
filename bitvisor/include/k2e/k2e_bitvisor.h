#ifndef K2E_BITVISOR_H
#define K2E_BITVISOR_H

#ifdef __cplusplus
namespace k2e {
  struct K2E;
}
using k2e::K2E;
#else
struct K2E;
#endif

struct ModuleDescriptor;
#ifdef __cplusplus
extern "C" {
#endif
extern struct K2E* g_k2e;

struct K2E* k2e_initialize();
void k2e_initplugins();

void k2e_on_module_load(struct K2E* k2e, struct ModuleDescriptor *module);

#ifdef __cplusplus
}
#endif

#endif
