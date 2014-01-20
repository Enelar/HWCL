#pragma once
#include "../stdafx.h"

#include "../program/instruction.h"
#include <memory>

namespace translator
{
  std::shared_ptr<program::instruction> Translate(const std::string &);

  struct unrecognized_instruction
  {
    std::string source;

    unrecognized_instruction(const std::string &_source)
      : source(_source)
    {

    }
  };
}