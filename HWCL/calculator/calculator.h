#pragma once
#include "../stdafx.h"

#include <functional>
#include "tree.h"

namespace calculator
{
  class calculator
  {
  public:
    typedef function<double(string)> get_callback;
  private:
    get_callback GetVariable;
    tree *calculation_tree = NULL;
  public:
    calculator(string expression);
    double Calculate(get_callback);

    ~calculator()
    {
      if (calculation_tree)
        delete calculation_tree;
    }
  };
}