#ifndef K2E_H
#define K2E_H

namespace k2e {

class Plugin;
class PluginsFactory;
class CorePlugin;
class Annotation;
class K2EExecutor;

class K2E
{
protected:
  PluginsFactory* m_pluginsFactory;

  CorePlugin* m_corePlugin;
  Annotation* m_annotation;
  K2EExecutor* m_k2eExecutor;

public:
  K2E();
  void init();
  void initPlugins();
  void initExecutor();  
  /** Get Core plugin */
  inline CorePlugin* getCorePlugin() const { return m_corePlugin; }
  K2EExecutor* getExecutor() { return m_k2eExecutor; }
};

}
#endif
