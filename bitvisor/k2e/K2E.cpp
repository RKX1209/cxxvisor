#include <k2e/K2E.hpp>
#include <k2e/Plugin.hpp>
#include <Plugins/CorePlugin.hpp>
#include <Plugins/Annotation.hpp>
#include <k2e/k2e_bitvisor.h>
#include <k2e/K2EExecutor.hpp>
#include <eh_frame_list.h>
extern "C" {
#include <core/printf.h>
}
extern void* __eh_frame_start;
extern void* __eh_frame_end;

namespace k2e {
void gg(char *buf) { printf("%s\n",buf); throw "gg error"; }
void ff(char *buf) { gg(buf);}
K2E::K2E()
{
  m_pluginsFactory = new PluginsFactory();
  PluginsFactory::registerPlugin(&CorePlugin::s_pluginInfo);
  m_corePlugin = static_cast<CorePlugin*>(
                m_pluginsFactory->createPlugin(this, "CorePlugin"));
  printf("K2E::init() fact = %p core = %p\n", m_pluginsFactory, m_corePlugin);
  char *buf = "from k2e::k2e()";
  try {
    ff(buf);
  }catch (char *hoge) {
    printf("Error: %s\n", hoge);
  }

}

void K2E::init()
{
}

void K2E::initPlugins()
{
  PluginsFactory::registerPlugin(&Annotation::s_pluginInfo);
  m_annotation = static_cast<Annotation*>(
                m_pluginsFactory->createPlugin(this, "Annotation"));
}

void K2E::initExecutor()
{
  m_k2eExecutor = new K2EExecutor(this);
}

}

static void __cxx_initialize()
{
  register_eh_frame(__eh_frame_start, (u64)__eh_frame_end - (u64)__eh_frame_start);
}

extern "C" {

K2E* g_k2e = 0;

K2E* k2e_initialize()
{
  K2E* k2e = (K2E*)new K2E();
  k2e->init();
  k2e->initPlugins();
  k2e->initExecutor();
  return k2e;
}

void cxx_initialize()
{
  __cxx_initialize();
}

}
