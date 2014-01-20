#pragma once
#include "../stdafx.h"

#include "instruction.h"
#include <vector>

namespace program
{
  class program : object
  {
    std::vector<instruction> code;
  };
}