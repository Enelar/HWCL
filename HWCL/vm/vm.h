#pragma once
#include "../stdafx.h"

#include <map>
#include <set>
#include "process_handler.h"

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
  };
}