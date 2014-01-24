#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class external : public instruction
    {
    public:
      external(const string &);

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

