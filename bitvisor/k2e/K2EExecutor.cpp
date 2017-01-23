extern "C" {
#include <core/printf.h>
}
#include <k2e/K2EExecutor.hpp>

namespace k2e {

K2EExecutor::K2EExecutor(K2E *k2e) : m_k2e(k2e)
{
  printf("K2EExecutor::K2EExecutor\n");
}

K2EExecutor::~K2EExecutor()
{

}

void K2EExecutor::execute()
{

}

}
