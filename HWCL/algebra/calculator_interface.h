#pragma once
#include "../stdafx.h"

#include <functional>

namespace algebra
{
  template<typename ret_type = vm::floating_point, typename req_type = void>
  class calculator_interface
  {
  protected:
    const string src_str;
  public:
    typedef ret_type ResultT;
    typedef req_type ArgumentT;

    calculator_interface(const string &expression);
    virtual ret_type Calculate(req_type) = 0;

    ~calculator_interface();
  };
}

#include "calculator_interface.hpp"