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

      external(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

