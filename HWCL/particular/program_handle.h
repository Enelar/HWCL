#pragma once
#include "remote_handle.h"

namespace particular
{
  struct program_handle : remote_handle
  {
    word hash;
  };
}