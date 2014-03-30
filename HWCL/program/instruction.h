#pragma once
#include "../stdafx.h"

namespace vm
{
  struct context;
};

namespace program
{
  struct instruction : object
  {
#ifdef _DEBUG_
    std::string DEBUG_TYPE;
#endif
    std::string source, without_comment;

    word code = 0;
  public:
    instruction(const std::string &, const std::string &_debug_name);
    instruction(const std::string &s)
      : instruction(s, "")
    {

    }

    const decltype(source) &Source() const;
    const decltype(source) &OriginalSource() const;

    virtual void Execute(vm::context &) = 0;
    virtual void Bind(vm::context &);

    virtual deque<ub> Serialize() 
    {
      return{};
    }
  };

  struct goto_instruction
  {
    word eip;
  };

  struct label_instruction
  {
    std::string name;
  };

  struct external_instruction
  {
    std::string name;
  };

  struct wait_instruction
  {
    flt wait;
    bool continues;
  };
}

#include "../vm/context.h"
