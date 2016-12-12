#ifndef _MODULE_DESCRIPTOR_H
#define _MODULE_DESCRIPTOR_H

#include <common/types.h>

struct ModuleDescriptor{
  //Virtual address where the module was loaded
  u64 LoadVBase;

  //Physical address where the module was loaded
  u64 LoadPBase;

  //The size of image of the module
  u64 Size;
};

#endif
