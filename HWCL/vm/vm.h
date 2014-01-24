#pragma once
namespace vm
{
  class virtual_machine;
}

#include "../stdafx.h"

#include <map>
#include <set>
#include "process_handler.h"
#include "context.h"

namespace vm
{
  class virtual_machine : object
  {
    word last_pid = 0;
    std::map<word, std::shared_ptr<process>> tasks;
    std::set<word> suspended;

  public:
    process_handler Execute(program::cached_program &);
    void Cycle();
    bool Idle() const;

    map<string, context::mapped_context> external_contexts;

    context::mapped_context GetExternalContext(const string &);
  };
}