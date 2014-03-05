#pragma once
#include "remote_handle.h"
#include "../vm/process_handler.h"

namespace particular
{
  struct process_handle : remote_handle
  {
    vm::process_handler ph;

    process_handle(vm::process_handler &&a)      : ph(a)    {    }

  };
}