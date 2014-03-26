#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class sequence : public instruction
    {
    public:
      sequence(const string &);

      sequence(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

