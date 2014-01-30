#pragma once
#include "../instruction.h"

namespace program
{
  namespace instructions
  {
    class local : public instruction
    {
      std::string init_value, name;
    public:
      local(const string &);

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

