#ifndef K2E_PLUGIN_HPP
#define K2E_PLUGIN_HPP

#include <limits.h>
#include <string>
#include <vector>
#include <set>

namespace k2e {
class K2E;
struct PluginInfo;

class Plugin {
private:
  K2E * m_k2e;
public:
  Plugin(K2E *k2e) : m_k2e(k2e){}

  /** Return associated K2E instance. */
  K2E* k2e() { return m_k2e; }
  const K2E* k2e() const { return m_k2e; }

  /** Initialize plugin. This function is called on initialization
      after all plugin instances have already been instantiated. */
  virtual void initialize();

  /** Return PluginInfo for this class. Defined by K2E_PLUGIN macro */
  virtual const PluginInfo* getPluginInfo() const = 0;

  //PluginState *getPluginState(S2EExecutionState *s, PluginState* (*f)(Plugin *, S2EExecutionState *)) const;

};

struct PluginInfo {
  /** Unique name of the plugin */
  std::string name;

  /** Human-readable description of the plugin */
  std::string description;

  /** Name of a plugin function (only one plugin is allowed for each function) */
  std::string functionName;

  /** A function to create a plugin instance */
  Plugin* (*instanceCreator)(K2E*);

};

class PluginsFactory {
private:
  //typedef std::map<std::string, const PluginInfo*> PluginsMap;
  //PluginsMap m_pluginsMap;
  std::vector<const PluginInfo*> m_pluginsList;
public:
  PluginsFactory();

  void registerPlugin(const PluginInfo *pluginInfo);

  const std::vector<const PluginInfo*>& getPluginInfoList() const;
  const PluginInfo* getPluginInfo(char *name) const;

  Plugin* createPlugin(K2E* k2e, char *name) const;
};

class CompiledPlugin {
public:
  typedef std::set<const PluginInfo *> CompiledPlugins;
private:
  static CompiledPlugins *s_compiledPlugins;
  CompiledPlugin();
public:
  CompiledPlugin(PluginInfo *info) {
    if (!s_compiledPlugins) {
      s_compiledPlugins = new CompiledPlugins();
    }
    s_compiledPlugins->insert(info);
    //PluginsFactory::registerPlugin(info);
  }
  static CompiledPlugins* getPlugins() {
    return s_compiledPlugins;
  }
};

/** Should be put at the beginning of any K2E plugin */
#define K2E_PLUGIN                                                                 \
  public:                                                                       \
    static char s_pluginDeps[][64];                                      \
    static PluginInfo s_pluginInfo;                                      \
  public:                                                                        \
    virtual PluginInfo* getPluginInfo() const { return &s_pluginInfo; }  \
    static PluginInfo* getPluginInfoStatic() { return &s_pluginInfo; }  \
  private:

#define K2E_DEFINE_PLUGIN(className, description, functionName, ...)      \
  char className::s_pluginDeps[][64] = { __VA_ARGS__ };                   \
  PluginInfo className::s_pluginInfo = {                                   \
      #className, description, functionName,                                     \
      _pluginCreatorHelper<className>                                            \
  }; \
  CompiledPlugin s_##className(className::getPluginInfoStatic())

template<class C>
Plugin* _pluginCreatorHelper(K2E* k2e) { return new C(k2e); }

}
#endif
