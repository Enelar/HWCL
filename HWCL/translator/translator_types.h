#pragma once

#include "fabric.h"
#include "../program/instructions.h"
#include "get_type_pos.h"

namespace translator
{
  using namespace program::instructions;
  typedef tuple
    <
    condition,
    program::instructions::end,
    external,
    jump,
    local,
    phase,
    read,
    send,
    sequence,
    set,
    step,
    wait,

    composite,
    label,
    nop //should be last
    > supported_instructions_list;

  typedef fabric<program::instruction, supported_instructions_list> Fabric;

  template<typename T>
  word InstructionCode()
  {
    return 1 + get_type_pos<T, supported_instructions_list>::Get();
  }
}