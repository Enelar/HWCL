#pragma once
#include "../stdafx.h"

#include <functional>
#include <list>

namespace calculator
{
  class tree
  {
    function<double(string)> GetVariable;

  public:
    void Build(string);
  };
}