#include <k2e/Plugin.hpp>
#include <k2e/K2E.hpp>
#include <core/string.h>
extern "C" {
#include <core/printf.h>
}

namespace k2e {

void Plugin::initialize(void)
{
}

struct list PluginsFactory::Plugins_head = { 0 }; //XXX: bit ugly
void PluginsFactory::registerPlugin(PluginInfo *pluginInfo)
{
  //printf("Factory::register %s\n", pluginInfo->name);
  LIST_APPEND(Plugins, pluginInfo);
}

const PluginInfo* PluginsFactory::getPluginInfo(char *name) const
{
  PluginInfo *pinfo;
  LIST_FOREACH(Plugins, pinfo)
  {
    if (!strcmp(pinfo->name, name))
    {
      return pinfo;
    }
  }
  return 0;

}
/** Plugin must be registered by registerPlugin before calling createPlugin. */
Plugin* PluginsFactory::createPlugin(K2E* k2e, char *name) const
{
  const PluginInfo *pluginInfo = getPluginInfo(name);
  if (pluginInfo)
    return pluginInfo->instanceCreator(k2e);
  else
    return 0;
}

}
