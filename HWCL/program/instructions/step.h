#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class step : public instruction
    {
    public:
      step(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

