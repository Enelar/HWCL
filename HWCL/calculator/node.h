#pragma once
#include "../stdafx.h"

#include <functional>

namespace calculator
{
  class node
  {
    function<double(string)> GetVariable;

  public:
    void Build(string);
  };
}