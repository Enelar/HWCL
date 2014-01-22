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

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

