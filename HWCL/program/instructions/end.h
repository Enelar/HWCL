#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class end : public instruction
    {
    public:
      end(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

