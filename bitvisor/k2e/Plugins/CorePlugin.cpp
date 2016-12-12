#include "CorePlugin.hpp"
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
  k2e->getCorePlugin()->onModuleLoad.emit(&params);
}

}
