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

    friend class parser::parser;
  };
}