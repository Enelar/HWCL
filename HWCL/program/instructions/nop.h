#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class nop : public instruction
    {
    public:
      nop(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

