#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class set : public instruction
    {
      std::string variable;
    public:
      set(const string &);

      void Execute(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

