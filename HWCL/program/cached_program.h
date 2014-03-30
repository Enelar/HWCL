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
    cached_program(const program &);


    const program *operator ->() const;

    const decltype(declval<program>().Code()) &Code() const;
  };
}