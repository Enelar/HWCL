#pragma once
#include "../../stdafx.h"
#include "../calculator_interface.h"

#include <functional>

namespace calculator
{
  class tree;
  class calculator : algebra::calculator_interface<vm::floating_point, function<double(string)>>
  {
  public:
    typedef ArgumentT get_callback;
  private:
    get_callback GetVariable;
    tree *calculation_tree = NULL;
  public:
    calculator(string expression);
    ResultT Calculate(get_callback);

    ~calculator();
  };

  struct calculation_failed
  {

  };

  struct syntax_error
  {

  };
}