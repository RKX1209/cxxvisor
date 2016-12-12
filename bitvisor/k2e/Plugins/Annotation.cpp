#include "Annotation.hpp"
extern "C" {
#include "core/printf.h"
}
#include <k2e/K2E.hpp>
#include <k2e/ModuleDescriptor.h>

namespace k2e {

K2E_DEFINE_PLUGIN(Annotation, "Plugin for monitoring module and bypasses functions", "Annotation");

void Annotation::initialize()
{
  k2e()->getCorePlugin()->onModuleLoad.connect(
                static_cast<Plugin*>(this),
                static_cast<K2ECallbackFunc_t>(&Annotation::onModuleLoad));
}

void Annotation::onModuleLoad(K2ECallbackParams *params)
{
  ModuleDescriptor *md = params->ml.md;
  printf("k2e: driver has loaded at 0x%llx(0x%llx): size=%llu\n",
        md->LoadVBase, md->LoadPBase, md->Size);
}

}
