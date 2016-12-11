#include "CorePlugin.hpp"
#include <k2e/K2E.hpp>

namespace k2e {
  K2E_DEFINE_PLUGIN(CorePlugin, "K2E core functionality", "Core", );
}
using namespace k2e;

void CorePlugin::initialize()
{

}

void k2e_on_module_load(ModuleDescriptor *module)
{

}
