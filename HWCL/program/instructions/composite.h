#pragma once
#include "../instruction.h"

#include <list>
#include <memory>

namespace program
{
  namespace instructions
  {
    class composite : public instruction
    {
    public:
      std::list<std::shared_ptr<instruction>> childs;

      composite(initializer_list<std::shared_ptr<instruction>>);
      composite(const string &);
      void Execute(vm::context &) override
      {
        throw_message("Meta instruction could not being executed");
      }

      static bool Signature(const string &);
    };
  }
}