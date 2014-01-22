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

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

