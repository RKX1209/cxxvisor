#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <common/list.h>
#include <core/mm.h>
#include <k2e/k2e_callback.hpp>

namespace sigc {

using namespace k2e;

struct K2ECallbackEntry {
  LIST_DEFINE (cb_func_list);
  K2ECallbackFunc_t func;
};

class signal {
private:
  LIST_DEFINE_HEAD(cb_func_list);
public:
  signal() {
  }
  void emit(K2ECallbackParams *cb_param) {
    struct K2ECallbackEntry *cb;
    LIST_FOREACH (cb_func_list, cb) {
      /* Call all connected functions */
      cb->func(cb_param);
    }
  }
  void connect(K2ECallbackFunc_t cb_func) {
    struct K2ECallbackEntry *cb;
    cb = (struct K2ECallbackEntry *)alloc(sizeof *cb);
    cb->func = cb_func;
    LIST_APPEND(cb_func_list, cb);
  }
};

}
#endif
