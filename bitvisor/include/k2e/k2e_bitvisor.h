#ifndef K2E_BITVISOR_H
#define K2E_BITVISOR_H

#include <stdint.h>

// hooked: 0
#define HOOK_TYPE_READ		0b110
#define HOOK_TYPE_WRITE		0b101
#define HOOK_TYPE_EXEC		0b011

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
void cxx_initialize();
void k2e_initplugins();

void k2e_on_module_load(struct K2E* k2e, struct ModuleDescriptor *module);
void k2e_register_hook(uint64_t*, uint32_t, uint8_t);
void k2e_register_hook_internal(uint64_t*, uint32_t, uint8_t);
uint8_t k2e_get_hooktype(uint64_t);
#ifdef __cplusplus
}
#endif

#endif
