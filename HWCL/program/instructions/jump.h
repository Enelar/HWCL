#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class jump : public instruction
    {
    public:
      jump(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

