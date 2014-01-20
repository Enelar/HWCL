#pragma once
#include "../stdafx.h"

#include <map>
#include "process.h"

namespace vm
{
  class virtual_machine : object
  {
    std::map<word, process> tasks;

  };
}