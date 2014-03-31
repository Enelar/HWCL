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

      end(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

