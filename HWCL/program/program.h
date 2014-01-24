#pragma once
#include "../stdafx.h"

#include "instruction.h"
#include <vector>
#include <memory>

namespace parser
{
  class parser;
}

namespace program
{
  class program : object
  {
    std::vector<std::shared_ptr<instruction>> code;
  public:
    const decltype(code) &Code() const;

    friend class parser::parser;
  };

  struct syntax_error
  {
    std::shared_ptr<instruction> instr;

    syntax_error() = default;

    syntax_error(std::shared_ptr<instruction> _i)
      : instr(_i)
    {

    }
  };
}