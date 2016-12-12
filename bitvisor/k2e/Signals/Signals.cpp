#include "Signals.hpp"
extern "C" {
#include <core/mm.h>
}
namespace sigc {
using namespace k2e;

void signal::emit(K2ECallbackParams *cb_param) {
  struct K2ECallbackEntry *cb;
  LIST_FOREACH (cb_func_list, cb) {
    /* Call all connected functions */
    K2ECallbackFunc_t func = cb->func;
    (cb->plugin->*func)(cb_param);
  }
}

void signal::connect(Plugin *plugin, K2ECallbackFunc_t cb_func) {
  struct K2ECallbackEntry *cb;
  cb = (struct K2ECallbackEntry *)alloc(sizeof *cb);
  cb->func = cb_func;
  cb->plugin = plugin;
  LIST_APPEND(cb_func_list, cb);
}

}
