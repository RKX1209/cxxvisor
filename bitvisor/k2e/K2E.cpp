#include <k2e/K2E.hpp>
#include <k2e/Plugin.hpp>
#include <Plugins/CorePlugin.hpp>
#include <Plugins/Annotation.hpp>
#include <k2e/k2e_bitvisor.h>
#include <k2e/K2EExecutor.hpp>
#include <eh_frame_list.h>
#include <crt.h>
extern "C" {
#include <core/printf.h>
}
extern u64 __eh_frame_start;
extern u64 __eh_frame_end;
extern u64 __init_array_start;
extern u64 __init_array_end;
extern u64 __fini_array_start;
extern u64 __fini_array_end;
extern u64 dataend;
extern u64 bss;

namespace k2e {
void gg(char *buf) { printf("%s\n",buf); throw "gg error"; }
void ff(char *buf) { gg(buf);}
K2E::K2E()
{
  m_pluginsFactory = new PluginsFactory();
  PluginsFactory::registerPlugin(&CorePlugin::s_pluginInfo);
  m_corePlugin = static_cast<CorePlugin*>(
                m_pluginsFactory->createPlugin(this, "CorePlugin"));
  printf("dataend=%p bss=%p\n", &dataend, &bss);
  printf("K2E::init() fact = %p core = %p\n", m_pluginsFactory, m_corePlugin);
  char *buf = "from k2e::k2e()";
  // try {
  //   ff(buf);
  // }catch (char *hoge) {
  //   printf("Error: %s\n", hoge);
  // }

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
  struct section_info_t sec_info = {0};

  sec_info.eh_frame_addr = &__eh_frame_start;
  sec_info.eh_frame_size = (u64)&__eh_frame_end - (u64)&__eh_frame_start;

  sec_info.init_array_addr = &__init_array_start;
  sec_info.init_array_size = (u64)&__init_array_end - (u64)&__init_array_start;

  sec_info.fini_array_addr = &__fini_array_start;
  sec_info.fini_array_size = (u64)&__fini_array_end - (u64)&__fini_array_start;

  local_init(&sec_info);
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
