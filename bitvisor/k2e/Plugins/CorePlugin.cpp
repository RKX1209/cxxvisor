#include "CorePlugin.hpp"
extern "C" {
#include <core/printf.h>
#include <core/types.h>
}
#include <k2e/K2E.hpp>

namespace k2e {
  K2E_DEFINE_PLUGIN(CorePlugin, "K2E core functionality", "Core", );
}
using namespace k2e;

void CorePlugin::initialize()
{
}

/******************************/
/* Functions called from Bitvisor */
extern "C" {

void k2e_on_module_load(K2E* k2e, struct ModuleDescriptor *module)
{
  K2ECallbackParams params;
  params.ml.md = module;
  //printf("k2e(%p)->getCorePlugin()(%p) %llx(%llx)\n", k2e, k2e->getCorePlugin(), params.ml.md->LoadVBase, params.ml.md->LoadPBase);
  k2e->getCorePlugin()->onModuleLoad.emit(&params);
}

void k2e_on_module_start(K2E* k2e, u64 pc)
{
  K2ECallbackParams params;
  
}

}
