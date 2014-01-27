#pragma once
#include "../stdafx.h"

#include <functional>

namespace calculator
{
  class tree;
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

    ~calculator();
  };
}