#ifndef K2E_EXECUTOR_HPP
#define K2E_EXECUTOR_HPP

namespace k2e {

class K2E;

class K2EExecutor {
protected:
  K2E *m_k2e;
public:
  K2EExecutor(K2E* k2e);
  virtual ~K2EExecutor();
  void execute();
};

class GlobalTest {
public:
  GlobalTest();
  ~GlobalTest();  
};

}
#endif
