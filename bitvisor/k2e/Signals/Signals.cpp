#include "Signals.hpp"
#include <k2e/Utils.h>
extern "C" {
#include <core/mm.h>
}
namespace sigc {
using namespace k2e;

void signal::emit(K2ECallbackParams *cb_param) {
  struct K2ECallbackEntry *cb;
  foreach2(it, m_cblist.begin(),m_cblist.end()) {
    /* Call all connected functions */
    K2ECallbackFunc_t func = (*it)->func;
    (cb->plugin->*func)(cb_param);
  }
}

void signal::connect(Plugin *plugin, K2ECallbackFunc_t cb_func) {
  struct K2ECallbackEntry *cb;
  cb = (struct K2ECallbackEntry *)alloc(sizeof *cb);
  cb->func = cb_func;
  cb->plugin = plugin;
  m_cblist.push_back(cb);
}

}
