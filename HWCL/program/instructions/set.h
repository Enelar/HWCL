#pragma once
#include "../instruction.h"

namespace calculator
{
  class calculator;
}

namespace program
{
  namespace instructions
  {
    class set : public instruction
    {
      calculator::calculator *proc = NULL;
      std::string variable, assignee;
    public:
      ~set();
      set(const string &);

      set(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

