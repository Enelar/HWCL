#pragma once
#include "../instruction.h"

#include <list>
#include <memory>

namespace program
{
  namespace instructions
  {
    class composite
    {
    public:
      std::list<std::shared_ptr<instruction>> childs;
    };
  }
}