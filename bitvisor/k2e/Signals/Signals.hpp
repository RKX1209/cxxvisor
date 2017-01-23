#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <limits.h>
#include <vector>
#include <k2e/ModuleDescriptor.h>
#include <k2e/k2e_callback.hpp>

namespace sigc {

using namespace k2e;

struct K2ECallbackEntry {
  Plugin *plugin;
  K2ECallbackFunc_t func;
};

class signal {
private:
  std::vector<K2ECallbackEntry*> m_cblist;
public:
  signal() {
  }
  void emit(K2ECallbackParams *cb_param);
  void connect(Plugin *plugin, K2ECallbackFunc_t cb_func);
};

}
#endif
