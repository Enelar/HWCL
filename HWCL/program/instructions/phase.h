#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class phase : public instruction
    {
    public:
      phase(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

