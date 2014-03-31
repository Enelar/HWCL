#pragma once

#include "../vm/context/context.h"

namespace particular
{
  struct box : ::vm::extern_context
  {
    int day, time, hour;
    box();
  };
}