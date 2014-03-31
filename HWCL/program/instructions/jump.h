#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class jump : public instruction
    {
      std::string name;
    public:
      jump(const string &);

      jump(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

