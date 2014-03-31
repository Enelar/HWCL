#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class send : public instruction
    {
    public:
      send(const string &);

      send(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

