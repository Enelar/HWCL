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

      void Execute(vm::context &) override;
      void Bind(vm::context &) override;

      static bool Signature(const string &);
    };
  }
}

