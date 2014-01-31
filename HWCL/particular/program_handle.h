#pragma once
#include "remote_handle.h"

namespace particular
{
  struct program_handle : remote_handle
  {
    word hash;

    program_handle(word _hash)
      : hash(_hash)
    {

    }
  };
}