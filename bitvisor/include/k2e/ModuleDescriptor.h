#ifndef _MODULE_DESCRIPTOR_H
#define _MODULE_DESCRIPTOR_H

#include <stdint.h>

struct ModuleDescriptor{
  //Virtual address where the module was loaded
  uint64_t LoadVBase;

  //Physical address where the module was loaded
  uint64_t LoadPBase;

  //The size of image of the module
  uint64_t Size;
};

#endif
