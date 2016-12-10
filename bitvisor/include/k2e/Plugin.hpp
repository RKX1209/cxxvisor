#ifndef K2E_PLUGIN_HPP
#define K2E_PLUGIN_HPP

namespace k2e {
class K2E;
struct PluginInfo;

class Plugin {
private:
  K2E * m_k2e;
public:
  Plugin(K2E *k2e) {}

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
  char* name;

  /** Human-readable description of the plugin */
  char* description;

  /** Name of a plugin function (only one plugin is allowed for each function) */
  char* functionName;

  /** A function to create a plugin instance */
  Plugin* (*instanceCreator)(K2E*);
};

/** Should be put at the beginning of any K2E plugin */
#define K2E_PLUGIN                                                                 \
  private:                                                                       \
    static const char s_pluginDeps[][64];                                      \
    static const PluginInfo s_pluginInfo;                                      \
  public:                                                                        \
    virtual const PluginInfo* getPluginInfo() const { return &s_pluginInfo; }  \
    static  const PluginInfo* getPluginInfoStatic() { return &s_pluginInfo; }  \
  private:

#define K2E_DEFINE_PLUGIN(className, description, functionName, ...)      \
  const char className::s_pluginDeps[][64] = { __VA_ARGS__ };                   \
  const PluginInfo className::s_pluginInfo = {                                   \
      #className, description, functionName,                                     \
      _pluginCreatorHelper<className>                                            \
  }; \

template<class C>
Plugin* _pluginCreatorHelper(K2E* k2e) { return new C(k2e); }
}
#endif
