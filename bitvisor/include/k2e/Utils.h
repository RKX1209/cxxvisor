#ifndef K2E_UTILS_H
#define K2E_UTILS_H

namespace k2e{

#define foreach2(_i, _b, _e) \
      for(typeof(_b) _i = _b, _i ## end = _e; _i != _i ## end;  ++ _i) 

}

#endif
