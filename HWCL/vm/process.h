#pragma once
#include "../stdafx.h"

#include "../program/cached_program.h"
#include "context.h"

namespace vm
{
  class process : object
  {
    program::cached_program p;
    word eip = 0; // next instruction

    context c;

  public:
    process(program::cached_program &);
  };
}