#pragma once
#include "../stdafx.h"

#include "../program/instruction.h"
#include <memory>

namespace translator
{
  std::shared_ptr<program::instruction> Translate(const std::string &);
  std::shared_ptr<program::instruction> Translate(const ub id, const deque<ub> &code);

  template<typename T>
  word InstructionCode();
  word InstructionCode(std::shared_ptr<program::instruction> &);

  std::shared_ptr<program::instruction> Deserialise(word code, deque<ub> args);

  struct unrecognized_instruction
  {
    std::string source;

    unrecognized_instruction(const std::string &_source)
      : source(_source)
    {

    }
  };
}