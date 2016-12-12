#include <k2e/K2E.hpp>
#include <k2e/Plugin.hpp>
#include <Plugins/CorePlugin.hpp>
#include <Plugins/Annotation.hpp>
#include <k2e/k2e_bitvisor.h>
extern "C" {
#include <core/printf.h>
}

namespace k2e {

K2E::K2E()
{
}

void K2E::init()
{
  m_pluginsFactory = new PluginsFactory();
  PluginsFactory::registerPlugin(&CorePlugin::s_pluginInfo);
  m_corePlugin = static_cast<CorePlugin*>(
                m_pluginsFactory->createPlugin(this, "CorePlugin"));
  //printf("K2E::init() fact = %p core = %p\n", m_pluginsFactory, m_corePlugin);
}

void K2E::initPlugins()
{
  PluginsFactory::registerPlugin(&Annotation::s_pluginInfo);
  m_annotation = static_cast<Annotation*>(
                m_pluginsFactory->createPlugin(this, "Annotation"));
}

}

extern "C" {

K2E* g_k2e = 0;

K2E* k2e_initialize()
{
  K2E* k2e = (K2E*)new K2E();
  k2e->init();
  return k2e;
}

void k2e_initplugins()
{
  g_k2e->initPlugins();
}

}
