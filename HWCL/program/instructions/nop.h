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

      nop(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

