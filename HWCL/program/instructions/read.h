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

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

