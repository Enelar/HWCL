#pragma once
#include "../stdafx.h"

#include "../vm/context.h"

namespace program
{
  struct instruction : object
  {
#ifdef _DEBUG_
    std::string debug_name;
#endif
    std::string source;
  public:
    instruction(const std::string &, const std::string &_debug_name);
    instruction(const std::string &s)
      : instruction(s, "")
    {

    }

    const std::string &Source() const;

    virtual void Execute(vm::context &) = 0;
  };

  struct goto_instruction
  {
    word eip;
  };
}
