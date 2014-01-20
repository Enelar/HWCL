#pragma once
#include "../stdafx.h"

#include "../vm/context.h"

namespace program
{
  struct instruction : object
  {
    std::string source;
  public:
    instruction(const std::string &);
    const std::string &Source() const;

    virtual void Execute(vm::context &) = 0;
  };
}
