#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class calculate : instruction
    {
    public:
      calculate(const string &);


      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

