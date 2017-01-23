#include <limits.h>
#include <vector>
#include <k2e/K2E.hpp>

#include <k2e/Plugin.hpp>
#include <Plugins/CorePlugin.hpp>
#include <Plugins/Annotation.hpp>

#include <k2e/Utils.h>

#include <k2e/k2e_bitvisor.h>
#include <k2e/K2EExecutor.hpp>
#include <eh_frame_list.h>
#include <crt.h>
#include <string>
#include <map>
#include <set>
extern "C" {
#include <core/printf.h>
}
extern uint64_t __eh_frame_start;
extern uint64_t __eh_frame_end;
extern uint64_t __init_array_start;
extern uint64_t __init_array_end;
extern uint64_t __fini_array_start;
extern uint64_t __fini_array_end;
extern uint64_t dataend;
extern uint64_t bss;

namespace k2e {
void gg(char *buf) { printf("%s\n",buf); throw "gg error"; }
void ff(char *buf) { gg(buf);}
K2E::K2E()
{
  //printf("dataend=%p bss=%p\n", &dataend, &bss);
  printf("K2E::init()\n");
  // std::vector<std::string> vec;
  // std::map<std::string, int> mp;
  //char buf[28];
  // for (int i = 0; i < 10; i++) {
  //   sprintf(buf, "string test %d", i);
  //   std::string str = buf;
  //   vec.push_back(str);
  //   printf("vec test: %s\n", vec[i]);
  // }
  // std::set<std::string> sts;
  // for (int i = 0; i < 10; i++) {
  //   sprintf(buf, "string test %d", i % 3);
  //   std::string str = buf;
  //   sts.insert(str);
  // }
  // for(auto itr = sts.begin(); itr != sts.end(); ++itr) {
  //   printf("sts test: %s\n", *itr);
  // }
  //mp[str] = 114514;
  //printf("string test: %s\n", str.c_str());
  //printf("vec test: %s\n", vec[0]);
  //printf("map test: %s\n", mp[str]);
  // try {
  //   ff(buf);
  // }catch (char *hoge) {
  //   printf("Error: %s\n", hoge);
  // }
  initExecutor();
  initPlugins();
}

void K2E::initPlugins()
{
  m_pluginsFactory = new PluginsFactory();
  m_annotation = static_cast<Annotation*>(
                m_pluginsFactory->createPlugin(this, "Annotation"));
  m_activePluginsList.push_back(m_annotation);

  //printf("k2e::initPlugins() fact = %p annot = %p\n", m_pluginsFactory, m_annotation);

  foreach2(it, m_activePluginsList.begin(), m_activePluginsList.end()) {
    (*it)->initialize();
  }
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
  sec_info.eh_frame_size = (uint64_t)&__eh_frame_end - (uint64_t)&__eh_frame_start;

  sec_info.init_array_addr = &__init_array_start;
  sec_info.init_array_size = (uint64_t)&__init_array_end - (uint64_t)&__init_array_start;

  sec_info.fini_array_addr = &__fini_array_start;
  sec_info.fini_array_size = (uint64_t)&__fini_array_end - (uint64_t)&__fini_array_start;
  local_init(&sec_info);
}

extern "C" {

K2E* g_k2e = 0;

K2E* k2e_initialize()
{
  K2E* k2e = (K2E*)new K2E();
  return k2e;
}

void cxx_initialize()
{
  __cxx_initialize();
}

}
