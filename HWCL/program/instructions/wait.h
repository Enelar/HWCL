#pragma once
#include "../instruction.h"
#include "../../algebra/calculator/calculator.h"

namespace program
{
  namespace instructions
  {
    class wait : public instruction
    {
      calculator::calculator *proc = nullptr;
      float until;

      float next_check = 0;
      bool active = false;
    public:
      wait(const string &);

      wait(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

