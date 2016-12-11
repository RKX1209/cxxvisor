#include <k2e/K2E.hpp>
#include <k2e/Plugin.hpp>
#include <Plugins/CorePlugin.hpp>
#include <k2e/k2e_bitvisor.h>

namespace k2e {

K2E::K2E()
{
  initPlugins();
}

void K2E::initPlugins()
{
  m_pluginsFactory = new PluginsFactory();
  m_corePlugin = static_cast<CorePlugin*>(
                m_pluginsFactory->createPlugin(this, "CorePlugin"));

}

}

extern "C" {

K2E *g_k2e = 0;

K2E *k2e_initialize()
{
  return (K2E*)new K2E();
}

}
