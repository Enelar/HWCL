#pragma once
#include "../stdafx.h"

#include "process.h"

namespace vm
{
  class process_handler
  {
    std::shared_ptr<process> p;
  public:
    process_handler(std::shared_ptr<process>);

    void Suspend();
    void Resume();
    void Terminate();
  };
}