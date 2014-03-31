#pragma once
#include "../instruction.h"

namespace algebra
{
  class comparator;
};
namespace program
{
  namespace instructions
  {
    class condition : public instruction
    {
      shared_ptr<instruction> then, otherwise;
      shared_ptr<algebra::comparator> comp;
    public:
      condition(const string &);

      condition(const deque<ub> &);
      deque<ub> Serialize() override;

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

