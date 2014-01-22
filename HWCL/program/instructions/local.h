#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class local : public instruction
    {
    public:
      local(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

