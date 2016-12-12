#ifndef ANNOTATION_HPP
#define ANNOTATION_HPP

#include <k2e/Plugin.hpp>
#include "CorePlugin.hpp"

namespace k2e {

class Annotation : public Plugin {
  K2E_PLUGIN
public:
  Annotation(K2E *k2e): Plugin(k2e) {}
  void initialize();
  void onModuleLoad(K2ECallbackParams *params);
};

}
#endif
