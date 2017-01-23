#include <k2e/Plugin.hpp>
#include <k2e/K2E.hpp>
#include <k2e/Utils.h>
extern "C" {
#include <core/printf.h>
}

namespace k2e {

using namespace std;

CompiledPlugin::CompiledPlugins* CompiledPlugin::s_compiledPlugins = NULL;

void Plugin::initialize(void)
{
}

PluginsFactory::PluginsFactory()
{
  CompiledPlugin::CompiledPlugins *plugins = CompiledPlugin::getPlugins();
  foreach2(it, plugins->begin(), plugins->end()) {
      registerPlugin(*it);
  }
}

void PluginsFactory::registerPlugin(const PluginInfo *pluginInfo)
{
  m_pluginsList.push_back(pluginInfo);
}

const vector<const PluginInfo*>& PluginsFactory::getPluginInfoList() const
{
    return m_pluginsList;
}

const PluginInfo* PluginsFactory::getPluginInfo(char *name) const
{
  CompiledPlugin::CompiledPlugins *plugins = CompiledPlugin::getPlugins();

  foreach2(it, plugins->begin(), plugins->end()) {
    if ((*it)->name == name) return *it;
  }
  return NULL;

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
