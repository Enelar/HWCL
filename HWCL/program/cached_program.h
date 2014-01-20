#pragma once
#include "../stdafx.h"

#include "program.h"
#include <memory>

namespace program
{
  class cached_program : object
  {
    std::shared_ptr<const program> original;
  public:
    operator const program &() const;
    operator program &();
  };
}