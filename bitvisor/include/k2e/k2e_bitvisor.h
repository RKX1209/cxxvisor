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

#ifdef __cplusplus
extern "C" {
#endif
extern struct K2E* g_k2e;

struct K2E* k2e_initialize();

#ifdef __cplusplus
}
#endif

#endif
