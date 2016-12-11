#ifndef K2E_H
#define K2E_H

namespace k2e {

class Plugin;
class PluginsFactory;
class CorePlugin;

class K2E
{
protected:
  PluginsFactory* m_pluginsFactory;

  CorePlugin* m_corePlugin;

  void initPlugins();
public:
  K2E();
  /** Get Core plugin */
  inline CorePlugin* getCorePlugin() const { return m_corePlugin; }
};

}
#endif
