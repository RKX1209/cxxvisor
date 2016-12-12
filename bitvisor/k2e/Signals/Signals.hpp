#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <common/list.h>
#include <k2e/ModuleDescriptor.h>
#include <k2e/k2e_callback.hpp>

namespace sigc {

using namespace k2e;

struct K2ECallbackEntry {
  LIST_DEFINE (cb_func_list);
  Plugin *plugin;
  K2ECallbackFunc_t func;
};

class signal {
private:
  LIST_DEFINE_HEAD(cb_func_list);
public:
  signal() {
  }
  void emit(K2ECallbackParams *cb_param);
  void connect(Plugin *plugin, K2ECallbackFunc_t cb_func);
};

}
#endif
