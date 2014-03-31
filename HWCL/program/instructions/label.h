#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class label : public instruction
    {
    public:
      label(const string &);

      label(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

