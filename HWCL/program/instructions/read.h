#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class read : public instruction
    {
      unique_ptr<instruction> compiled;
    public:
      read(const string &);

      read(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

