#ifndef K2E_CORE_PLUGIN_H
#define K2E_CORE_PLUGIN_H

#include <k2e/Plugin.hpp>
#include "../Signals/Signals.hpp"

namespace k2e {

class CorePlugin : public Plugin {
  K2E_PLUGIN
public:
  CorePlugin(K2E *k2e): Plugin(k2e) {

  }
  void initialize();

};

}
#endif
