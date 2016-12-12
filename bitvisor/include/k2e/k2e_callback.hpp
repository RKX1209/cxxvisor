#ifndef K2E_CALLBACK_HPP
#define K2E_CALLBACK_HPP

class ModuleDescriptr;

namespace k2e {

class Plugin;

typedef struct _K2EModuleLoadParams
{
  ModuleDescriptor *md;
} K2EModuleLoadParams;

typedef struct _K2ECallbackParams
{
  union {
    K2EModuleLoadParams ml;
  };
} K2ECallbackParams;

typedef void (Plugin::*K2ECallbackFunc_t) (K2ECallbackParams*);
}

#endif
